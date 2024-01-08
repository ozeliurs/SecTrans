//
// Created by Maxime BILLY on 08/01/2024.
//

// Parse arguments
//
// -up <filepath> : upload a file to the server
// -down <filepath> : download a file from the server
// -list : list all files on the server

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/bidirectionnal_client.h"
#include "../include/base64.h"
#include <stdio.h>
#include <dirent.h>

void usage() {
    fprintf(stdout, "Usage: sectrans <command> [args]\n");
    fprintf(stdout, "Commands:\n");
    fprintf(stdout, "  -up <filepath> : upload a file to the server\n");
    fprintf(stdout, "  -down <filepath> : download a file from the server\n");
    fprintf(stdout, "  -list : list all files on the server\n");
}

int upload(char *filepath) {
    /* Sends UP and the full filepath and then the file content in base64 separated by char 31 */
    start();

    char* separator = "\x1F";

    // Open the file in read mode
    FILE *file = fopen(filepath, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening the file at %s\n", filepath);
        return 1; // Return an error code
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Create a buffer large enough to contain the file
    char *buffer = malloc(fileSize + 1);

    // Read the file into the buffer
    fread(buffer, fileSize, 1, file);

    // Close the file
    fclose(file);

    // Encode the file in base64
    char *encodedFile = base64_encode(buffer, fileSize);

    // Check if encoding was successful
    if (encodedFile == NULL) {
        printf("Error encoding the file.\n");
        return 2; // Return an error code
    }

    // Create the message
    char *msg = malloc(strlen("UP") + strlen(filepath) + 2 + fileSize + 1);

    // Check if memory allocation was successful
    if (msg == NULL) {
        printf("Memory allocation error.\n");
        fclose(file);
        return 2; // Return an error code
    }

    // Send UP and filepath
    strcpy(msg, "UP");
    strcat(msg, separator);
    strcat(msg, filepath);      // TODO remove null terminator
    strcat(msg, separator);
    strcat(msg, encodedFile);

    // Send the message
    int result = put(msg);

    // Check if error
    if (result != 0) {
        fprintf(stderr, "Failed to send message to the server\n");
        return 1;
    }

    // Free memory
    free(buffer);
    free(encodedFile);
    free(msg);

    stop();

    return 0;
}

int download(char *filepath) {
    return 1;
}

int list() {
    /* Sends LS and then listen for the response and print it */
    start();

    char* msg = "LS";

    // Send the message
    int result = put(msg);

    // Check if error
    if (result != 0) {
        fprintf(stderr, "Failed to send message to the server\n");
        return 1;
    }

    // Get the response
    char* response = get();

    // Check if error
    if (response == NULL) {
        fprintf(stderr, "Failed to get response from the server\n");
        return 1;
    }

    // Print the response
    printf("%s\n", response);

    // Free memory
    free(response);

    stop();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "-up") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: sectrans -up <filepath>\n");
            return 1;
        }

        return upload(argv[2]);
    } else if (strcmp(command, "-down") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: sectrans -down <filepath>\n");
            return 1;
        }

        return download(argv[2]);
    } else if (strcmp(command, "-list") == 0) {
        if (argc > 2) {
            fprintf(stderr, "Usage: sectrans -list\n");
            return 1;
        }

        return list();
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        usage();
        return 1;
    }

    return 0;
}

