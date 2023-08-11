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
#include "../lib/tcpsock.h"
#include "../lib/dplist.h"

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
ClientList *root, *now;
static dplist_t *socket_list; /* List of info clients are accepted by server */

void catch_ctrl_c_and_exit(int sig)
{
    ClientList *tmp;

    while (root != NULL)
    {
        printf("\nClose socketfd: %d\n", root->data);
        close(root->data); // close all socket include server_sockfd
        tmp = root;
        root = root->link;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

// void send_to_all_clients(tcpsock_t *np, char tmp_buffer[])
// {
//     tcpsock_t *tmp = socket_list->head->next;

//     while (tmp != NULL)
//     {
//         if (np->sd != tmp->sd) /* all clients except itself */
//         {
//             printf("Send to sockfd %d: \"%s\" \n", tmp->sd, tmp_buffer);
//             send(tmp->sd, tmp_buffer, LENGTH_SEND, 0);
//         }
//         tmp = tmp->next;
//     }
// }

void client_handler(void *p_client)
{
    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    // ClientList *np = (ClientList *)p_client;
    tcpsock_t *np = (tcpsock_t *)p_client;

    /* Naming */
    if (recv(np->sd, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME - 1)
    {
        printf("%s didn't input name.\n", np->ip_addr);
        leave_flag = 1;
    }
    else
    {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s(%s)(%d) join the chatroom.\n", np->name, np->ip_addr, np->sd);
        sprintf(send_buffer, "%s(%s) join the chatroom.", np->name, np->ip_addr);
        // send_to_all_clients(np, send_buffer);
    }

    /* Conversation */
    while (1)
    {
        if (leave_flag)
        {
            num_of_clients--;
            break;
        }

        int receive = recv(np->sd, recv_buffer, LENGTH_MSG, 0);
        printf("Value of receive: %d\n", receive);
        if (receive > 0)
        {
            if (strcmp(recv_buffer, "num") == 0)
            {
                printf("%s(%s)(%d) requests the number people of the chatroom.\n", np->name, np->ip_addr, np->sd);
                sprintf(send_buffer, "%s(%s) %d: the number people of the chatroom.", np->name, np->ip_addr, num_of_clients);
                send(np->sd, send_buffer, LENGTH_SEND, 0);
                continue;
            }

            if (strlen(recv_buffer) == 0)
            {
                continue;
            }
            sprintf(send_buffer, "%s：%s from %s", np->name, recv_buffer, np->ip_addr);
        }
        else if (receive == 0 || strcmp(recv_buffer, "exit") == 0)
        {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip_addr, np->sd);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip_addr);
            leave_flag = 1;
        }
        else
        {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }
        // send_to_all_clients(np, send_buffer);
    }

    // Remove Node
    // close(np->sd);
    // if (np == now)
    // { // remove an edge node
    //     now = np->prev;
    //     now->link = NULL;
    // }
    // else
    // { // remove a middle node
    //     np->prev->link = np->link;
    //     np->link->prev = np->prev;
    // }
    // free(np);
}

int main(int argc, char const *argv[])
{
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
    printf("Start Server on: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    /* Initialize Linked List for Clients */
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;

    tcpsock_t *client = tcp_sock_create(); /* Storing the incoming client connection */
    socket_list = dpl_create(NULL, NULL, NULL);
    while (1)
    {
        // client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);

        // /* Print Client IP */
        // getpeername(client_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);
        // printf("Client %s:%d come in.\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        // client->sd = client_sockfd;
        // strncpy(client->ip_addr, inet_ntoa(client_info.sin_addr), 16);
        // strncpy(client->name, "NULL", 5);

        // printf("%s\n", client->ip_addr);
        
        tcp_wait_for_connection_remake(server_sockfd, &client);
        
        /* Append linked list for clients */
        // ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
        // c->prev = now;
        // now->link = c;
        // now = c;
        // num_of_clients++;

        dpl_insert_at_index(socket_list, client, 0, false);
        dpl_print_heap(socket_list);

        pthread_t id;
        if (pthread_create(&id, NULL, (void *)client_handler, (void *)client) != 0)
        {
            perror("Create pthread error!\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}