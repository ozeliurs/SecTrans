//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_SECURE_BI_CLIENT_H
#define SECTRANS_SECURE_BI_CLIENT_H

#include "rsa.h"
#include "../../src/include/bidirectionnal_client.h"

RSA *client_private_key = NULL;
RSA *server_public_key = NULL;

int secure_start() {
    // Start the client's server
    int ret = start();

    // Generate RSA key pair
    client_private_key = generateRSAKeyPair();

    // Get the public key string
    char *publicKeyStr = getPublicKeyStr(client_private_key);

    printf("Client public key: %s\n", publicKeyStr);

    // Send the public key to the server
    int sendResult = put(publicKeyStr);

    // Free the string
    free(publicKeyStr);

    // Wait for the public key from the server
    char *serverPublicKeyStr = get();

    // Read the public key from the string
    server_public_key = readPublicKeyFromStr(serverPublicKeyStr);

    // Free the string
    free(serverPublicKeyStr);

    return ret;
}

int secure_stop() {

}

int secure_put(char *msg) {

}

char* secure_get() {

}

#endif //SECTRANS_SECURE_BI_CLIENT_H
