//
// Created by Maxime BILLY on 05/01/2024.
//

#include "../../src/include/advanced_server.h"
#include <stdio.h>

int main() {
    startserver(8080);
    char* msg = _get();
    printf("Message from client: %s\n", msg);
    free(msg);
    stopserver();
}