//
// Created by Maxime BILLY on 21/12/2023.
//

#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <cstring>

void uploadCommand(const char* file) {
    std::cout << "Executing upload command with file: " << file << "\n";
    // Add your upload logic here
}

void downloadCommand(const char* file) {
    std::cout << "Executing download command with file: " << file << "\n";
    // Add your download logic here
}

void listCommand() {
    std::cout << "Executing list command\n";
    // Add your list logic here
}

void helpCommand(const std::string& command) {
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
            {"list",     no_argument,       nullptr, 'l'},
            {nullptr,    0,                 nullptr, 0}
    };

    int option;
    while ((option = getopt_long(argc, argv, "ud:l", long_options, nullptr)) != -1) {
        switch (option) {
            case 'u':
                uploadCommand(optarg);
                break;

            case 'd':
                downloadCommand(optarg);
                break;

            case 'l':
                listCommand();
                break;

            default:
                helpCommand(argv[0]);
                std::exit(EXIT_FAILURE);
        }
    }

    return 0;
}
