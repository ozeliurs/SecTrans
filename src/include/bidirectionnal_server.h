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
    startserver(SERVER_PORT);
}

int stop() {
    stopserver();
}

int put(char *msg) {
    return _put(msg, CLIENT_PORT);
}

char* get() {
    return _get();
}

#endif //SECTRANS_BIDIRECTIONNAL_SERVER_H
