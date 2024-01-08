//
// Created by Maxime BILLY on 05/01/2024.
//
#include <stdio.h>
#include "../../src/include/server.h"


int main() {
    startserver(8080);
    char msg_read[1024];
    getmsg(msg_read);
    printf("Message from client: %s\n", msg_read);
    stopserver();
}