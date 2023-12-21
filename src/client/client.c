//
// Created by Maxime BILLY on 21/12/2023.
//

#include "client.h"
#include <string.h>

int main(int argc, char *argv[]) {
    char msg[1024];

    // Fill msg with "Hello World!"
    strcpy(msg, "Hello World!");

    sndmsg(msg, 8080);
}