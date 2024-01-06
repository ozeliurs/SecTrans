//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_SECURE_BI_CLIENT_H
#define SECTRANS_SECURE_BI_CLIENT_H

#include "rsa.h"
#include "../../src/include/bidirectionnal_server.h"

RSA *client_private_key = NULL;
RSA *server_public_key = NULL;

int secure_start() {
    // Start the server
    int ret = start();

    // Generate RSA key pair
    client_private_key = generateRSAKeyPair();

    // Get the public key string
    char *publicKeyStr = getPublicKeyStr(client_private_key);

    // Send the public key to the server
    int sendResult = put(publicKeyStr);

    // Receive the public key from the server
    char *serverPublicKeyStr = get();

    // Read the public key from the string
    server_public_key = readPublicKeyFromStr(serverPublicKeyStr);

    // Free the strings
    free(publicKeyStr);
    free(serverPublicKeyStr);

    return ret;
}

int secure_stop() {
    // Free the RSA key pair
    RSA_free(client_private_key);
    RSA_free(server_public_key);

    // Stop the server
    return stop();
}

int secure_put(char *msg) {
    // Encrypt the message
    char *encryptedMessage;
    int encryptResult = encryptMessage(msg, server_public_key, &encryptedMessage);
    if (encryptResult == -1) {
        fprintf(stderr, "Error encrypting message\n");
        return -1;
    }

    // Send the encrypted message to the server
    int sendResult = put(encryptedMessage);

    // Free the encrypted message
    free(encryptedMessage);

    return sendResult;
}

char* secure_get() {
    // Get the encrypted message from the server
    char *encryptedMessage = get();

    // Decrypt the message
    char *decryptedMessage;
    int decryptResult = decryptMessage(encryptedMessage, client_private_key, &decryptedMessage);
    if (decryptResult == -1) {
        fprintf(stderr, "Error decrypting message\n");
        return NULL;
    }

    // Free the encrypted message
    free(encryptedMessage);

    return decryptedMessage;
}

#endif //SECTRANS_SECURE_BI_CLIENT_H
