//
// Created by Maxime BILLY on 06/01/2024.
//

#include "../../src/include/rsa.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Generate RSA key pair
    RSA *keyPair = generateRSAKeyPair();
    if (keyPair == NULL) {
        fprintf(stderr, "Error generating RSA key pair\n");
        return 1;
    }

    // Get the public key string
    char *publicKeyStr = getPublicKeyStr(keyPair);
    if (publicKeyStr == NULL) {
        fprintf(stderr, "Error getting public key string\n");
        RSA_free(keyPair);
        return 1;
    }

    // Print the public key string
    printf("Public Key:\n%s\n", publicKeyStr);

    // Read the public key from the string
    RSA *readPublicKey = readPublicKeyFromStr(publicKeyStr);
    if (readPublicKey == NULL) {
        fprintf(stderr, "Error reading public key from string\n");
        RSA_free(keyPair);
        free(publicKeyStr);
        return 1;
    }

    // Encrypt and decrypt a message
    const char *originalMessage = "Hello, RSA!";
    char *encryptedMessage;
    int encryptResult = encryptMessage(originalMessage, readPublicKey, &encryptedMessage);
    if (encryptResult == -1) {
        fprintf(stderr, "Error encrypting message\n");
        RSA_free(keyPair);
        RSA_free(readPublicKey);
        free(publicKeyStr);
        return 1;
    }

    char *decryptedMessage;
    int decryptResult = decryptMessage(encryptedMessage, keyPair, &decryptedMessage);
    if (decryptResult == -1) {
        fprintf(stderr, "Error decrypting message\n");
        RSA_free(keyPair);
        RSA_free(readPublicKey);
        free(publicKeyStr);
        free(encryptedMessage);
        return 1;
    }

    // Print the results
    printf("Original Message: %s\n", originalMessage);
    printf("Encrypted Message: %s\n", encryptedMessage);
    printf("Decrypted Message: %s\n", decryptedMessage);

    // Free allocated memory
    RSA_free(keyPair);
    RSA_free(readPublicKey);
    free(publicKeyStr);
    free(encryptedMessage);
    free(decryptedMessage);

    return 0;
}
