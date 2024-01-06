//
// Created by Maxime BILLY on 06/01/2024.
//

#include "../../src/include/bidirectionnal_server.h"
#include <stdio.h>

int main() {
    start();
    char *msg = get();
    printf("Message from client: %s\n", msg);
    free(msg);
    char msg_to_send[] = "Hello, Client!";
    put(msg_to_send);
    stop();
}
