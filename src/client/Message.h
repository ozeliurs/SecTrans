//
// Created by Maxime BILLY on 23/12/2023.
//

#ifndef SECTRANS_MESSAGE_H
#define SECTRANS_MESSAGE_H

#include <string>
#include <iostream>


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


#endif //SECTRANS_MESSAGE_H
