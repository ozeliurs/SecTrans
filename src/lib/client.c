//
// Created by Maxime BILLY on 08/01/2024.
//

#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

const char leng[] = "1025";

/* Sends a *null-terminated* string to the specified port.
 * Returns 0 on success, -1 on failure.
 */
int sndmsg(char msg[1024], int port)
{
    struct sockaddr_in addr;
    char dest[1032];
    strncpy(dest, msg, 1024);
    dest[1024] = '\0';
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if ( fd >= 0 )
    {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        if ( inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) > 0 )
        {
            if ( connect(fd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) >= 0 )
            {
                send(fd, leng, sizeof(leng), 0);
                send(fd, dest, strlen(dest), 0);
                close(fd);
                return 0;
            }
            else
            {
                puts("\nConnection Failed ");
                return -1;
            }
        }
        else
        {
            puts("\nInvalid address/ Address not supported ");
            return -1;
        }
    }
    else
    {
        puts("\n Socket creation error ");
        return -1;
    }
}