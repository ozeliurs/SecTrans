//
// Created by Maxime BILLY on 05/01/2024.
//
#include <stdio.h>
#include "../../src/include/client.h"

int main() {
    int port = 8080;

    char msg_to_send[] = "Hello, Server!";
    int result = sndmsg(msg_to_send, port);

    if (result != 0) {
        fprintf(stderr, "Failed to send message to the server\n");
        return 1;
    }

    printf("Message sent to the server: %s\n", msg_to_send);

    return 0;
}