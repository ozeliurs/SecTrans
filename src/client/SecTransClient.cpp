//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransClient.h"

#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <cstring>
#include <filesystem>
#include "../lib/ultimateClient.h"
#include "../lib/ultimateServer.h"

SecTransClient::SecTransClient() {
    startserver(CLIENT_PORT);
}

SecTransClient::~SecTransClient() throw() {
    stopserver();
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
    startserver(CLIENT_PORT);
    std::string msg;

    receive(msg);

    std::cout << msg << std::endl;
}