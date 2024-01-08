//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_BIDIRECTIONNAL_CLIENT_H
#define SECTRANS_BIDIRECTIONNAL_CLIENT_H

#include "advanced_client.h"
#include "advanced_server.h"

int CLIENT_PORT = 8080;
int SERVER_PORT = 8081;

int start() {
    printf("Client has started.\n");
    return startserver(CLIENT_PORT);
}

int stop() {
    printf("Client has stopped.\n");
    return stopserver();
}

int put(char *msg) {
    printf("Client has put.\n");
    return _put(msg, SERVER_PORT);
}

char* get() {
    printf("Client has get.\n");
    return _get();
}

#endif //SECTRANS_BIDIRECTIONNAL_CLIENT_H
