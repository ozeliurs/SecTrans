//
// Created by Maxime BILLY on 23/12/2023.
//

#ifndef SECTRANS_SECTRANSCLIENT_H
#define SECTRANS_SECTRANSCLIENT_H

#include "../lib/client.h"
#include "../lib/server.h"
#include <iostream>
#include "Message.h"

class SecTransClient {
private:
    static const int CLIENT_PORT = 8080;
    static const int SERVER_PORT = 8081;
public:
    SecTransClient();
    ~SecTransClient() throw();
    void upload(const char *file);
    void download(const char *file);
    void list();
};


#endif //SECTRANS_SECTRANSCLIENT_H
