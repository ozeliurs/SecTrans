//
// Created by Maxime BILLY on 23/12/2023.
//

#include "SecTransServer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "../lib/ultimateClient.h"
#include "../lib/ultimateServer.h"

/*
[main] Building folder: SecTrans SecTransClient
[build] Starting build
[proc] Executing command: /usr/bin/cmake --build /home/ozeliurs/SecTrans/build --config Debug --target SecTransClient -j 4 --
[build] [ 66%] Building CXX object CMakeFiles/SecTransClient.dir/src/client/client.cpp.o
[build] [ 66%] Building CXX object CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o
[build] [100%] Linking CXX executable SecTransClient
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `send(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateClient.h:8: multiple definition of `send(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int)'; CMakeFiles/SecTransClient.dir/src/client/client.cpp.o:/home/ozeliurs/SecTrans/src/client/../lib/ultimateClient.h:8: first defined here
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `start(int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:8: multiple definition of `start(int)'; CMakeFiles/SecTransClient.dir/src/client/client.cpp.o:/home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:8: first defined here
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `stop()':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:13: multiple definition of `stop()'; CMakeFiles/SecTransClient.dir/src/client/client.cpp.o:/home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:13: first defined here
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `receive(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:18: multiple definition of `receive(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&)'; CMakeFiles/SecTransClient.dir/src/client/client.cpp.o:/home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:18: first defined here
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/client.cpp.o: in function `send(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateClient.h:28: undefined reference to `sndmsg(char*, int)'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/client.cpp.o: in function `start(int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:10: undefined reference to `startserver(int)'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/client.cpp.o: in function `stop()':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:15: undefined reference to `stopserver()'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/client.cpp.o: in function `receive(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:26: undefined reference to `getmsg(char*)'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `send(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateClient.h:28: undefined reference to `sndmsg(char*, int)'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `start(int)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:10: undefined reference to `startserver(int)'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `stop()':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:15: undefined reference to `stopserver()'
[build] /usr/bin/ld: CMakeFiles/SecTransClient.dir/src/client/SecTransClient.cpp.o: in function `receive(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&)':
[build] /home/ozeliurs/SecTrans/src/client/../lib/ultimateServer.h:26: undefined reference to `getmsg(char*)'
[build] collect2: error: ld returned 1 exit status
[build] gmake[3]: *** [CMakeFiles/SecTransClient.dir/build.make:122: SecTransClient] Error 1
[build] gmake[2]: *** [CMakeFiles/Makefile2:97: CMakeFiles/SecTransClient.dir/all] Error 2
[build] gmake[1]: *** [CMakeFiles/Makefile2:104: CMakeFiles/SecTransClient.dir/rule] Error 2
[build] gmake: *** [Makefile:137: SecTransClient] Error 2
[proc] The command: /usr/bin/cmake --build /home/ozeliurs/SecTrans/build --config Debug --target SecTransClient -j 4 -- exited with code: 2
[driver] Build completed: 00:00:01.285
[build] Build finished with exit code 2
*/

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

