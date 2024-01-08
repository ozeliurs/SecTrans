//
// Created by Maxime BILLY on 08/01/2024.
//

#include "../include/bidirectionnal_server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

DIR *dir = NULL;

int list() {
    // List all files in the storage directory
    struct dirent *ent;
    char *list = (char *) malloc(1024 * sizeof(char));
    list[0] = '\0';

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            strcat(list, ent->d_name);
            strcat(list, "\n");
        }
    }

    return list;
}

int download(char *filename) {
    // Open file
    char *filepath = (char *) malloc((strlen(filename) + 10) * sizeof(char));
    strcpy(filepath, "./storage/");
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filepath);
        return 1;
    }

    // Get file size
    fseek(file, 0L, SEEK_END);
    int filesize = ftell(file);
    rewind(file);

    // Read file
    char *contents = (char *) malloc(filesize * sizeof(char));
    fread(contents, sizeof(char), filesize, file);

    // Close file
    fclose(file);

    return contents;
}

int upload(char *contents) {
    // Find char(31) in contents and split the string in 2
    char *separator = (char *) malloc(2 * sizeof(char));
    separator[0] = 31;
    separator[1] = '\0';
    char *filename = strtok(contents, separator);
    char *filecontents = strtok(NULL, separator);

    // Open file
    char *filepath = (char *) malloc((strlen(filename) + 10) * sizeof(char));
    strcpy(filepath, "./storage/");
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "w");

    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filepath);
        return 1;
    }

    // Write file
    fwrite(filecontents, sizeof(char), strlen(filecontents), file);

    // Close file
    fclose(file);

    return 0;
}

int main() {
    // Start listening and enter an infinite loop
    dir = opendir("./storage");

    // If directory does not exist, create it
    if (dir == NULL) {
        mkdir("./storage", 0777);
        dir = opendir("./storage");
    }

    // Accept connections
    start();

    while (1) {
        // Get message from client
        char *msg = get();

        if (msg == NULL) {
            fprintf(stderr, "Failed to read message from client\n");
            stop();  // Ensure to stop the server even if an error occurs
            return 1;
        }

        printf("Message from client: %s\n", msg);

        // get the first 2 chars in the message in action
        char* action = (char*)malloc(2 * sizeof(char));
        strncpy(action, msg, 2);

        // If action is LS, call list
        if (strcmp(action, "LS") == 0) {
            char* list_str = list();
            put(list_str);
            free(list_str);
        }

        // If action is DL, call download
        if (strcmp(action, "DL") == 0) {
            char* filename = (char*)malloc((strlen(msg) - 2) * sizeof(char));
            strncpy(filename, msg + 3, strlen(msg) - 2);
            char* contents = download(filename);
            put(contents);
            free(filename);
            free(contents);
        }

        // If action is UP, call upload
        if (strcmp(action, "UP") == 0) {
            // find char(23) in msg and split the string in 2
            char* contents = (char*)malloc((strlen(msg) - 2) * sizeof(char));
            strncpy(contents, msg + 3, strlen(msg) - 2);
            upload(contents);
        }

        // Send message to client
        put(msg);
    }
}