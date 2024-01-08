//
// Created by Maxime BILLY on 08/01/2024.
//

#include <stdint.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int server_fd;
struct sockaddr_in address;

/* Starts the server on the specified port
 * Exits on failure.
 * Returns 0 on success.
 */
int startserver(uint16_t port)
{
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if ( server_fd < 0 )
    {
        perror("socket failed");
        exit(1);
    }
    int reuseport = true;
    if ( setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof(reuseport)) )
    {
        perror("setsockopt");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = 0;
    address.sin_port = htons(port);
    if ( bind(server_fd, (const struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0 )
    {
        perror("bind failed");
        exit(1);
    }
    int result = listen(server_fd, 3);
    if ( result < 0 )
    {
        perror("listen");
        exit(1);
    }
    return result;
}

ssize_t valread;
int new_socket;
socklen_t addrlen = sizeof(struct sockaddr_in);

/* Blocks until a message is received and write it to the buffer.
 * The message must be a null-terminated string at most 1024 characters long (null character excluded).
 * Exits on failure.
 * Returns 0 on success.
 */
int getmsg(char msg_read[1024])
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if ( new_socket < 0 )
    {
        perror("accept");
        exit(1);
    }
    valread = read(new_socket, buf, 5);
    int len = atoi(buf);
    valread = read(new_socket, buf, len);
    close(new_socket);
    strcpy(msg_read, buf);
    return 0;
}

/* Stops the server.
 * Returns 0.
 */
int stopserver()
{
    close(server_fd);
    return 0;
}

int main()
{
    int port = 8080;
    startserver(port);
    printf("Server started on port %d\n", port);
    char msg_read[1024];
    int bytesRead = getmsg(msg_read);
    if ( bytesRead < 0 )
    {
        fprintf(stderr, "Failed to read message from client\n");
        stopserver();
        return 1;
    }
    printf("Message from client: %s\n", msg_read);
    stopserver();
    printf("Server stopped\n");
    return 0;
}