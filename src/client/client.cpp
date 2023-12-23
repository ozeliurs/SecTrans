//
// Created by Maxime BILLY on 21/12/2023.
//

#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <cstring>
#include "../lib/client.h"

enum Action {
    UPLOAD,
    DOWNLOAD,
    LIST
};


class Message {
private:
    Action action;
    std::string filename;
    int MESSAGE_SIZE = 1024;
public:
    Message(Action action, std::string filename) {
        this->action = action;
        this->filename = filename;
    }

    char *toString() {
        std::string str;

        switch (action) {
            case UPLOAD:
                str[0] = 'U';
                break;
            case DOWNLOAD:
                str[0] = 'D';
                break;
            case LIST:
                str[0] = 'L';
                break;
        }

        if (filename.length() > MESSAGE_SIZE - 1) {
            std::cerr << "File name is too long (max " << MESSAGE_SIZE - 1 << " characters)" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        str = str + filename;

        return (char *) str.c_str();
    }
};

class Client {
public:
    void upload(const char *file) {
        std::string filename = file;
        sndmsg(Message(UPLOAD, filename).toString(), 8080);
    }

    void download(const char *file) {
        std::string filename = file;
        sndmsg(Message(DOWNLOAD, filename).toString(), 8080);
    }

    void list() {
        sndmsg(Message(LIST, "").toString(), 8080);
    }
};

void helpCommand(const std::string &command) {
    std::cout << "Executing help command\n";
    std::cerr << "Usage: " << std::endl;
    std::cerr << "\t" << command << " --upload <file>" << std::endl;
    std::cerr << "\t" << command << " --list" << std::endl;
    std::cerr << "\t" << command << " --download <file>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        helpCommand(argv[0]);
        std::exit(EXIT_FAILURE);
    }

    static struct option long_options[] = {
            {"upload",   required_argument, nullptr, 'u'},
            {"download", required_argument, nullptr, 'd'},
            {"list",     no_argument,       nullptr, 'l'}
    };

    Client client = Client();

    int option;
    while ((option = getopt_long(argc, argv, "ud:l", long_options, nullptr)) != -1) {
        switch (option) {
            case 'u':
                client.upload(optarg);
                break;

            case 'd':
                client.download(optarg);
                break;

            case 'l':
                client.list();
                break;

            default:
                helpCommand(argv[0]);
                std::exit(EXIT_FAILURE);
        }
    }

    return 0;
}