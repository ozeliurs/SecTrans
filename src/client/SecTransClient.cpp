//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransClient.h"

SecTransClient::SecTransClient() {
    startserver(CLIENT_PORT);
}

SecTransClient::~SecTransClient() throw() {
    stopserver();
}

void SecTransClient::upload(const char *file) {
    std::string filename = file;
    char msg[1024];
    Message(UPLOAD, filename).toString(msg);
    sndmsg(msg, SERVER_PORT);
}

void SecTransClient::download(const char *file) {
    std::string filename = file;
    char msg[1024];
    Message(DOWNLOAD, filename).toString(msg);
    sndmsg(msg, SERVER_PORT);
}

void SecTransClient::list() {
    char msg[1024];
    Message(LIST, "").toString(msg)
    sndmsg(msg, SERVER_PORT);

    char msg[1024];
    getmsg(msg);
    std::cout << msg << std::endl;
}
