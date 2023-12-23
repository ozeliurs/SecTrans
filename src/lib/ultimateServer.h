#ifndef ULTIMATE_SERVER_H
#define ULTIMATE_SERVER_H

#include <iostream>
#include <string>
#include "server.h"

int start(int port){
    std::cout << "Starting server on port " << port << std::endl;
    return startserver(port);
}

int stop() {
    std::cout << "Stopping server" << std::endl;
    return stopserver();
}

int receive(std::string &message) {
    std::cout << "Receiving message" << std::endl;

    int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE] = {0};
    int return_value = 0;

    while (true) {
        int rv = getmsg(buffer);
        
        if (rv == -1) {
            return_value = -1;
        }

        message += std::string(buffer);
    }
    
    return return_value;
}

#endif