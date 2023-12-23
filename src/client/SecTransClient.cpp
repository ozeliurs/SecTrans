//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransClient.h"

SecTransClient::SecTransClient() {
    start(CLIENT_PORT);
}

SecTransClient::~SecTransClient() throw() {
    stop();
}

void SecTransClient::upload(std::string filename) {
    // U[filename]
    std::string message = "U" + filename;

    send(message, SERVER_PORT);
    // Upload file
}

void SecTransClient::download(std::string filename) {
    std::string message = "D" + filename;
    send(message, SERVER_PORT);
    // Download File
}

void SecTransClient::list() {
    send("L", SERVER_PORT);
    start(CLIENT_PORT);
    std::string msg;

    receive(msg);

    std::cout << msg << std::endl;
}