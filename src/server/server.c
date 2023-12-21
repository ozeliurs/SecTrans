//
// Created by Maxime BILLY on 21/12/2023.
//

#include <stdio.h>
#include "server.h"

int main(int argc, char *argv[]) {
    startserver(8080);

    char msg[1024];
    getmsg(msg);
    printf("Message received: %s\n", msg);

    // stopserver();
}