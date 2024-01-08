//
// Created by Maxime BILLY on 05/01/2024.
//

#ifndef SECTRANS_ADVANCED_CLIENT_H
#define SECTRANS_ADVANCED_CLIENT_H

#include "client.h"
#include <stdio.h>

/* Sends chuncks of 1024 bytes via client.h and finished with a EOF(char 0) */
int _put(char *msg, int port) {
    // Send chunks of 1024 bytes
    int i = 0;

    while (msg[i] != '\0') {
        // Create chunk
        char chunk[1024];
        int j = 0;

        // Copy msg into chunk
        while (j < 1023 && msg[i] != '\0') {
            chunk[j] = msg[i];
            i++;
            j++;
        }

        // If chunk is not full, fill it with '\0'
        while (j <= 1023) {
            chunk[j] = '\0';
            j++;
        }

        // Send chunk
        int result = sndmsg(chunk, port);

        printf("Sent %d bytes\n", j);

        // Check if error
        if (result != 0) {
            fprintf(stderr, "Failed to send message to the server\n");
            return 1;
        }
    }

    return 0;
}

#endif //SECTRANS_ADVANCED_CLIENT_H
