//
// Created by Maxime BILLY on 05/01/2024.
//

#ifndef SECTRANS_ADVANCED_CLIENT_H
#define SECTRANS_ADVANCED_CLIENT_H

#include "client.h"

int MESSAGE_SIZE = 1024;

/* Sends chuncks of MESSAGE_SIZE bytes via client.h, chuncks are ETB(char 23) separated and finished with a EOF(char 0) */
int _put(char *msg, int port) {
    // Send chunks of MESSAGE_SIZE bytes
    int i = 0;

    printf("Sending message: %s\n", msg);

    while (msg[i] != '\0') {
        // Create chunk
        char chunk[MESSAGE_SIZE];
        int j = 0;

        // Copy msg into chunk
        while (j < (MESSAGE_SIZE - 1) && msg[i] != '\0') {
            chunk[j] = msg[i];
            i++;
            j++;
        }

        printf("Chunk Size: %d\n", j);

        // If chunk is not full, fill it with '\0'
        while (j <= (MESSAGE_SIZE - 1)) {
            printf("Filling chunk with \\0\n");
            chunk[j] = '\0';
            j++;
        }

        // Send chunk
        printf("Sending chunk: %s\n", chunk);
        int result = sndmsg(chunk, port);

        // Check if error
        if (result != 0) {
            fprintf(stderr, "Failed to send message to the server\n");
            return 1;
        }
    }

    return 0;
}

#endif //SECTRANS_ADVANCED_CLIENT_H
