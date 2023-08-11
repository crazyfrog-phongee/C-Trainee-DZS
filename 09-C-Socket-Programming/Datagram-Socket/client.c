#include <netinet/in.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#define BUF_SIZE 10
#define PORT_NUM 50002

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr;
    int fd;
    ssize_t numBytes;
    char *send_buf = "HelloWorld";
    ssize_t send_buf_len;
    char resp[BUF_SIZE];
    
    send_buf_len = strlen(send_buf);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        handle_error("socket()");
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
    {
        printf("inet_pton failed for address '%s'", argv[1]);
    }

    if (sendto(fd, send_buf, send_buf_len, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) != send_buf_len)
    {
        handle_error("sendto()");
    }
    numBytes = recvfrom(fd, resp, BUF_SIZE, 0, NULL, NULL);
    if (numBytes == -1)
    {
        handle_error("recvfrom()");
    }
    else
        printf("Response : %s\n", resp);

    return 0;
}