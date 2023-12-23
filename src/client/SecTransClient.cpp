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
    sndmsg(Message(UPLOAD, filename).toString(), SERVER_PORT);
}

void SecTransClient::download(const char *file) {
    std::string filename = file;
    sndmsg(Message(DOWNLOAD, filename).toString(), SERVER_PORT);
}

void SecTransClient::list() {
    sndmsg(Message(LIST, "").toString(), SERVER_PORT);
    char msg[1024];
    getmsg(msg);
    std::cout << msg << std::endl;
}
