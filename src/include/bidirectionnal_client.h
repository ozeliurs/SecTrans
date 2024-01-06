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
    startserver(CLIENT_PORT);
}

int stop() {
    stopserver();
}

int send(char *msg) {
    return _put(msg, SERVER_PORT);
}

char* receive() {
    return get();
}

#endif //SECTRANS_BIDIRECTIONNAL_CLIENT_H
