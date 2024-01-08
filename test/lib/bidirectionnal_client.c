//
// Created by Maxime BILLY on 06/01/2024.
//

#include "../../src/include/bidirectionnal_client.h"
#include <stdio.h>

int main() {
    start();
    char msg_to_send[] = "Hello, Server!";
    put(msg_to_send);
    char *msg = get();
    printf("Message from client: %s\n", msg);
    free(msg);
    stop();
}