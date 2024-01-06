//
// Created by Maxime BILLY on 23/12/2023.
//

#ifndef SECTRANS_SECTRANSCLIENT_H
#define SECTRANS_SECTRANSCLIENT_H

#include <iostream>
#include "../include/ultimateClient.h"
#include "../include/ultimateServer.h"

class SecTransClient {
private:
    static const int CLIENT_PORT = 8080;
    static const int SERVER_PORT = 8081;
public:
    SecTransClient();
    ~SecTransClient() throw();
    void upload(std::string filename);
    void download(std::string filename);
    void list();
};


#endif //SECTRANS_SECTRANSCLIENT_H
