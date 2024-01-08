//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_BIDIRECTIONNAL_SERVER_H
#define SECTRANS_BIDIRECTIONNAL_SERVER_H

#include "advanced_client.h"
#include "advanced_server.h"

int CLIENT_PORT = 8080;
int SERVER_PORT = 8081;

int start() {
    printf("Server has started.\n");
    return startserver(SERVER_PORT);
}

int stop() {
    printf("Server has stopped.\n");
    return stopserver();
}

int put(char *msg) {
    printf("Server has put. Message: %s\n", msg);
    return _put(msg, CLIENT_PORT);
}

char* get() {
    printf("Server has get.\n");
    return _get();
}

#endif //SECTRANS_BIDIRECTIONNAL_SERVER_H
