//
// Created by Maxime BILLY on 06/01/2024.
//

#include "secure_bi_server.h"
#include <stdio.h>

int main() {
    // Start the secure server
    int startResult = secure_start();
    if (startResult == -1) {
        fprintf(stderr, "Error starting the secure server\n");
        return -1;
    }

    // Example: Send a message from the client to the server
    char* messageFromClient = "Hello, Server!";
    int sendResult = secure_put(messageFromClient);
    if (sendResult == -1) {
        fprintf(stderr, "Error sending message from client to server\n");
        return -1;
    }

    // Example: Receive a message from the client
    char* receivedMessage = secure_get();
    if (receivedMessage != NULL) {
        printf("Received message from client: %s\n", receivedMessage);
        free(receivedMessage);
    } else {
        fprintf(stderr, "Error receiving message from client\n");
    }

    // Stop the secure server
    int stopResult = secure_stop();
    if (stopResult == -1) {
        fprintf(stderr, "Error stopping the secure server\n");
        return -1;
    }

    return 0;
}
