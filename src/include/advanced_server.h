//
// Created by Maxime BILLY on 05/01/2024.
//

#ifndef SECTRANS_ADVANCED_SERVER_H
#define SECTRANS_ADVANCED_SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

/* read message sent by client */
char* _get() {
    // Allocate memory for the message

    char* msg = (char*)malloc(1024);

    int i = 0;
    while (1) {
        // Create a buffer to store the message chunk
        char chunk[1024];

        // Get message chunk
        int result = getmsg(chunk);

        // Check if error
        if (result < 0) {
            fprintf(stderr, "Failed to get message from the client\n");
            exit(1);
        }

        // Allocate memory for the new message
        char* new_msg = (char*)malloc(i + 1024);

        // Check if error
        // TODO check memory allocation
        if (new_msg == NULL){
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
        // Copy old message into new message
        strcpy(new_msg, msg);

        // Free old message
        free(msg);

        // Set new message
        msg = new_msg;

        // Copy chunk into msg until 1024 bytes or EOF
        int j = 0;
        while (j < 1024 && chunk[j] != '\0') {
            msg[i] = chunk[j];
            i++;
            j++;
        }

        // If chunk is not full, stop reading
        if (j < (1024 - 1)) {
            break;
        }
    }

    return msg;
}

#endif //SECTRANS_ADVANCED_SERVER_H
