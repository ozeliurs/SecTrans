//
// Created by Maxime BILLY on 06/01/2024.
//

#include "../../src/include/bidirectionnal_server.h"

int main() {
    start();
    char *msg = get();
    free(msg);
    char msg_to_send[] = "Hello, Client!";
    put(msg_to_send);
    stop();
}
