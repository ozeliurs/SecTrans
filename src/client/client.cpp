//
// Created by Maxime BILLY on 21/12/2023.
//

#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <cstring>
#include "SecTransClient.h"

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

     SecTransClient client = SecTransClient();

    int option;
    option = getopt_long(argc, argv, "ud:l", long_options, nullptr);
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

    return 0;
}