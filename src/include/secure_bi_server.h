//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_SECURE_BI_SERVER_H
#define SECTRANS_SECURE_BI_SERVER_H

#include "rsa.h"
#include "bidirectionnal_server.h"

RSA *server_private_key = NULL;
RSA *client_public_key = NULL;

int secure_start() {
    // Start the server
    int ret = start();

    // Generate RSA key pair
    server_private_key = generateRSAKeyPair();

    // Wait for the public key from the client
    char *clientPublicKeyStr = get();

    // Read the public key from the string
    client_public_key = readPublicKeyFromStr(clientPublicKeyStr);

    // Free the string
    free(clientPublicKeyStr);

    // Get the public key string
    char *publicKeyStr = getPublicKeyStr(server_private_key);

    // Send the public key to the client
    int sendResult = put(publicKeyStr);

    // Free the string
    free(publicKeyStr);

    return ret;
}

int secure_stop() {
    // Free the RSA key pair
    RSA_free(server_private_key);
    RSA_free(client_public_key);

    // Stop the server
    return stop();
}

int secure_put(char *msg) {
    // Encrypt the message
    char *encryptedMessage;
    int encryptResult = encryptMessage(msg, client_public_key, &encryptedMessage);
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

char *secure_get() {
    // Receive the encrypted message from the client
    char *encryptedMessage = get();

    // Decrypt the message
    char *decryptedMessage;
    int decryptResult = decryptMessage(encryptedMessage, server_private_key, &decryptedMessage);
    if (decryptResult == -1) {
        fprintf(stderr, "Error decrypting message\n");
        return NULL;
    }

    // Free the encrypted message
    free(encryptedMessage);

    return decryptedMessage;
}

#endif //SECTRANS_SECURE_BI_SERVER_H