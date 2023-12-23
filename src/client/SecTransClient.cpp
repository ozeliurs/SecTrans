//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransClient.h"
#include "../lib/client.h"
#include <iostream>
#include "Message.h"

void SecTransClient::upload(const char *file) {
    std::string filename = file;
    sndmsg(Message(UPLOAD, filename).toString(), 8080);
}

void SecTransClient::download(const char *file) {
    std::string filename = file;
    sndmsg(Message(DOWNLOAD, filename).toString(), 8080);
}

void SecTransClient::list() {
    sndmsg(Message(LIST, "").toString(), 8080);
}
