#ifndef ULTIMATE_CLIENT_H
#define ULTIMATE_CLIENT_H

#include <iostream>
#include <string>
#include "client.h"

int send(std::string message, int server_port) {
    std::cout << "Sending message: " << message << std::endl;

    if (message.find('\0') != std::string::npos) {
        std::cerr << "Error: message contains '\\0'" << std::endl;
        return -1;
    }

    int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE] = {0};
    int return_value = 0;

    for (int i = 0; i < message.length(); i += BUFFER_SIZE) {
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (i + j < message.length()) {
                buffer[j] = message[i + j];
            } else {
                buffer[j] = '\0'; //😀⛄️
            }
        }
        int rv = sndmsg(buffer, server_port);
        if (rv == -1) {
            return_value = -1;
        }
    }

    return return_value;
}

#endif //ULTIMATE_CLIENT_H