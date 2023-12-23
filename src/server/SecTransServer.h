//
// Created by Maxime BILLY on 23/12/2023.
//

#ifndef SECTRANS_SECTRANSSERVER_H
#define SECTRANS_SECTRANSSERVER_H

#include "../lib/ultimateClient.h"
#include <iostream>


class SecTransServer{
private:
    static const int CLIENT_PORT = 8080;
    static const int SERVER_PORT = 8081;
    char buffer[102400] = {0};
    static const int BUFFER_SIZE = 102400;
    std::string filename;
    int size = 0;
public:
    SecTransServer();
    ~SecTransServer() throw();
    void treatMessage(std::string message);
};

#endif //SECTRANS_SECTRANSSERVER_H