//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransServer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "../include/ultimateClient.h"
#include "../include/ultimateServer.h"

namespace fs = std::filesystem;

SecTransServer::SecTransServer() {
    start(SERVER_PORT);
    filename="";

    while (true) {
        std::string message;

        receive(message);
        treatMessage(message);
    }
}

void SecTransServer::treatMessage(std::string message){
    {
        if (message[0] == 'U') {
            //U[filename]

            if(fs::exists(message.substr(1))){
                send("File already present\n", CLIENT_PORT);
                return;
            }

            filename = message.substr(1);
            return;
        }

        if (message[0] == 'R') {
            if (filename == ""){
                send("ESet filename first\n", CLIENT_PORT);
                return;
            }

            std::ofstream file(filename);
            
            if (file.is_open()) {
                file << message.substr(1);
                file.close();
                filename = "";
            }
            return;
        }
        
        if (message[0] == 'D') {
            if(!fs::exists(message.substr(1))){
                send("EFile not found\n", CLIENT_PORT);
            }else{
                std::ifstream fileIn;
                fileIn.open(message.substr(1), std::ios::binary);
                if (!fileIn.is_open()) {
                    send("EError Opening the file \n", CLIENT_PORT);
                }else{
                    
                    std::string message((std::istreambuf_iterator<char>(fileIn)), std::istreambuf_iterator<char>());

                    message = 'S' + message;

                    fileIn.close();

                    send(message, CLIENT_PORT);
                }
            }
            return;
        }
        
        if (message[0] == 'L') {
            fs::path currentDir = fs::current_path();

            std::ostringstream messageos;
            messageos << "List:" << std::endl;

            for(const auto& entry: fs::directory_iterator(currentDir)) {
                if (fs::is_regular_file(entry.path())) {
                    messageos << entry.path().filename() << std::endl;
                }
            }
            
            std::string message = messageos.str();

            send(message,CLIENT_PORT);
            return;
        }

        
        std::exit(EXIT_FAILURE);
        
    }
}


SecTransServer::~SecTransServer() throw() {
    stop();
}

