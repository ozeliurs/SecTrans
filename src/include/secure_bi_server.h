//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_SECURE_BI_SERVER_H
#define SECTRANS_SECURE_BI_SERVER_H

#include <openssl/dh.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "rsa.h"
#include "bidirectionnal_server.h"


// Function to handle errors
void handleErrors(void) {
    fprintf(stderr, "Error occurred\n");
    exit(EXIT_FAILURE);
}

AES_KEY aesKey;

int secure_start() {
    // Start the server
    if (start() == -1) {
        fprintf(stderr, "Failed to start the server.\n");
        return -1;  // Return failure
    }

    DH *alice_dh = DH_new();
    if (!alice_dh) handleErrors();

    // Generate parameters for Alice
    if (1 != DH_generate_parameters_ex(alice_dh, 128, DH_GENERATOR_2, NULL)) handleErrors();

    // Generate public and private keys for Alice
    if (1 != DH_generate_key(alice_dh)) handleErrors();

    // Convert Alice's public key to a string
    unsigned char *alice_pub_key_str;
    int alice_pub_key_len = i2d_DHparams(alice_dh, &alice_pub_key_str);
    if (alice_pub_key_len <= 0) handleErrors();

    // Send Alice's public key to Bob
    if (put((char *)alice_pub_key_str) != 0) handleErrors();

    // Receive Bob's public key
    char *bob_pub_key_str = get();

    DH *bob_dh = DH_new();
    if (!bob_dh) handleErrors();

    // Convert received public key string to DH structure
    if (!d2i_DHparams(&bob_dh, (const unsigned char **)&bob_pub_key_str, strlen(bob_pub_key_str))) handleErrors();

    // Generate public and private keys for Bob
    if (1 != DH_generate_key(bob_dh)) handleErrors();

	// Derive shared secret on Alice's side
	unsigned char *alice_shared_secret = (unsigned char *)malloc(DH_size(alice_dh));
	if (!alice_shared_secret) handleErrors();

	int alice_shared_secret_len = DH_compute_key(alice_shared_secret, bob_dh->pub_key, alice_dh);
	if (alice_shared_secret_len <= 0) handleErrors();

	// Allocate memory for bob_shared_secret_str and bob_shared_secret
	unsigned char *bob_shared_secret_str = (unsigned char *)malloc(DH_size(bob_dh));
	unsigned char *bob_shared_secret = (unsigned char *)malloc(DH_size(bob_dh));
	if (!bob_shared_secret_str || !bob_shared_secret) handleErrors();

	// Convert received shared secret string to binary
	if (!d2i_DHparams(&bob_dh, (const unsigned char **)&bob_shared_secret_str, strlen(bob_shared_secret_str))) handleErrors();

    // Print the shared secret
    printf("Shared Secret: ");
    for (int i = 0; i < alice_shared_secret_len; ++i) {
        printf("%02x", alice_shared_secret[i]);
    }
    printf("\n");

    // Use the shared secret for AES encryption and decryption
    AES_KEY aesKey;
    if (AES_set_encrypt_key(alice_shared_secret, 128, &aesKey) != 0) handleErrors();

    const char *plaintext = "Hello, Bob! This is a secret message.";

    // Encrypt the message
    unsigned char ciphertext[AES_BLOCK_SIZE];
    AES_encrypt((const unsigned char *)plaintext, ciphertext, &aesKey);

    // Send the ciphertext to Bob
    if (put((char *)ciphertext) != 0) handleErrors();

    // Clean up
    DH_free(alice_dh);
    DH_free(bob_dh);
    free(alice_shared_secret);
    free(bob_shared_secret);
}

int secure_stop() {

}

int secure_put(char *msg) {

}

char *secure_get() {

}

#endif //SECTRANS_SECURE_BI_SERVER_H
