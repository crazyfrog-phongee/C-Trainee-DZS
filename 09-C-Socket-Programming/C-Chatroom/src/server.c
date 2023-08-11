#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "proto.h"
#include "server.h"

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define BACKLOG 5

/* Global Variable Definition */
int server_sockfd, client_sockfd;
int num_of_clients;
static pthread_mutex_t num_of_clients_mutex;
ClientList *root, *now;

void catch_ctrl_c_and_exit(int sig)
{
    ClientList *tmp;

    while (root != NULL)
    {
        printf("\n%ld Close socketfd: %d\n", time(NULL), root->data);
        close(root->data); /* Close all socket include server_sockfd */
        tmp = root;
        root = root->link;
        free(tmp);
    }

    pthread_mutex_destroy(&num_of_clients_mutex);

    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

void send_to_all_clients(ClientList *np, char tmp_buffer[])
{
    ClientList *tmp = root->link;

    while (tmp != NULL)
    {
        if (np->data != tmp->data) /* All clients except itself */
        {
            printf("%ld Send to sockfd %d: \"%s\" \n", time(NULL), tmp->data, tmp_buffer);
            send(tmp->data, tmp_buffer, LENGTH_SEND, 0);
        }
        tmp = tmp->link;
    }
}

ClientList *add_client(int client_sockfd, struct sockaddr_in client_info)
{
    ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
    c->prev = now;
    now->link = c;
    now = c;

    pthread_mutex_lock(&num_of_clients_mutex);
    num_of_clients++;
    pthread_mutex_unlock(&num_of_clients_mutex);
    
    return c;
}

void client_handler(void *p_client)
{
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)p_client;

    /* Handle Input Name */
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME - 1)
    {
        printf("%ld %s didn't input name.\n", time(NULL), np->ip);
        leave_flag = 1;
    }
    else
    {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%ld %s(%s)(%d) join the chatroom.\n", time(NULL), np->name, np->ip, np->data);
        sprintf(send_buffer, "%s join the chatroom.", np->name);
        send_to_all_clients(np, send_buffer);
    }

    /* Handling Conversation */
    while (1)
    {
        if (leave_flag)
        {
            pthread_mutex_lock(&num_of_clients_mutex);
            num_of_clients--;
            pthread_mutex_unlock(&num_of_clients_mutex);
            break;
        }

        /* Waiting for receiving data from client */
        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0)
        {
            /* Request the number people of the chatroom */
            if (strcmp(recv_buffer, "num") == 0)
            {
                printf("%ld %s(%s)(%d) requests the number people of the chatroom.\n", time(NULL), np->name, np->ip, np->data);
                sprintf(send_buffer, "%s: Having %d people of the chatroom.", np->name, num_of_clients);
                send(np->data, send_buffer, LENGTH_SEND, 0);
                continue;
            }

            if (strlen(recv_buffer) == 0)
            {
                continue;
            }

            /* Normal message */
            sprintf(send_buffer, "%s：%s", np->name, recv_buffer);
        }
        else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) /* Exit request */
        {
            printf("%ld %s(%s)(%d) leave the chatroom.\n", time(NULL), np->name, np->ip, np->data);
            sprintf(send_buffer, "%s leave the chatroom.", np->name);
            leave_flag = 1;
        }
        else
        {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
        send_to_all_clients(np, send_buffer);
    }

    /* Remove client from linked list */
    close(np->data);
    if (np == now) /* remove an edge node */
    {
        now = np->prev;
        now->link = NULL;
    }
    else /* remove a middle node */
    {
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }

    free(np);
}

int main(int argc, char const *argv[])
{
    /* Establish SIGINT handler */
    signal(SIGINT, catch_ctrl_c_and_exit);

    /* 1. TCP Passive Open */
    /* 1.1 Create socket */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1)
    {
        handle_error("socket()");
    }

    /* 1.2 Initialize Server Address */
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);

    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);

    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(8888);

    /* 1.3 Bind and Listen */
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    /* Log Server Info */
    getsockname(server_sockfd, (struct sockaddr *)&server_info, (socklen_t *)&s_addrlen);
    printf("%ld Start Server on: %s:%d\n", time(NULL), inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    /* Initialize Linked List for Clients */
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;
    pthread_mutex_init(&num_of_clients_mutex, NULL);

    while (1)
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);

        /* Print Client IP */
        getpeername(client_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);
        printf("%ld Client %s:%d come in.\n", time(NULL), inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        /* Append linked list for clients */
        ClientList *cur_client = add_client(client_sockfd, client_info);

        pthread_t id;
        if (pthread_create(&id, NULL, (void *)client_handler, (void *)cur_client) != 0)
        {
            perror("Create pthread error!\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}