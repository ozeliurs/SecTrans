//
// Created by Maxime BILLY on 06/01/2024.
//

#include "../../src/include/secure_bi_client.h"
#include <stdio.h>

int main() {
    // Start the secure client
    int startResult = secure_start();
    if (startResult == -1) {
        fprintf(stderr, "Error starting the secure client\n");
        return -1;
    }

    // Example: Send a message from the server to the client
    char* messageFromServer = "Hello, Client!";
    int sendResult = secure_put(messageFromServer);
    if (sendResult == -1) {
        fprintf(stderr, "Error sending message from server to client\n");
        return -1;
    }

    // Example: Receive a message from the server
    char* receivedMessage = secure_get();
    if (receivedMessage != NULL) {
        printf("Received message from server: %s\n", receivedMessage);
        free(receivedMessage);
    } else {
        fprintf(stderr, "Error receiving message from server\n");
    }

    // Stop the secure client
    int stopResult = secure_stop();
    if (stopResult == -1) {
        fprintf(stderr, "Error stopping the secure client\n");
        return -1;
    }

    return 0;
}
