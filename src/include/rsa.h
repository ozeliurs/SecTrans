//
// Created by Maxime BILLY on 06/01/2024.
//

#ifndef SECTRANS_RSA_H
#define SECTRANS_RSA_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// Function to generate RSA key pair
RSA *generateRSAKeyPair() {
    RSA *rsa = NULL;
    BIGNUM *bne = NULL;

    int bits = 2048; // Adjust the key size as needed

    bne = BN_new();
    BN_set_word(bne, RSA_F4);

    rsa = RSA_new();
    RSA_generate_key_ex(rsa, bits, bne, NULL);

    BN_free(bne);
    return rsa;
}

// Function to encrypt a message using RSA public key
int encryptMessage(const char *plainText, RSA *publicKey, char **encryptedText) {
    int rsaSize = RSA_size(publicKey);
    *encryptedText = (char *) malloc(rsaSize);

    int result = RSA_public_encrypt(strlen(plainText), (const unsigned char *) plainText,
                                    (unsigned char *) *encryptedText, publicKey, RSA_PKCS1_OAEP_PADDING);

    if (result == -1) {
        fprintf(stderr, "Error encrypting message: %s\n", ERR_error_string(ERR_get_error(), NULL));
    }

    return result;
}

// Function to decrypt a message using RSA private key
int decryptMessage(const char *encryptedText, RSA *privateKey, char **decryptedText) {
    int rsaSize = RSA_size(privateKey);
    *decryptedText = (char *) malloc(rsaSize);

    int result = RSA_private_decrypt(rsaSize, (const unsigned char *) encryptedText, (unsigned char *) *decryptedText,
                                     privateKey, RSA_PKCS1_OAEP_PADDING);

    return result;
}

RSA *readPublicKeyFromStr(const char *keyStr) {
    BIO *bio = BIO_new_mem_buf(keyStr, -1);
    if (bio == NULL) {
        perror("Error creating BIO");
        return NULL;
    }

    RSA *rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    if (rsa == NULL) {
        perror("Error reading public key from string");
        BIO_free(bio);
        return NULL;
    }

    BIO_free(bio);
    return rsa;
}

char *getPublicKeyStr(RSA *rsa) {
    BIO *bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        perror("Error creating BIO");
        return NULL;
    }

    if (PEM_write_bio_RSA_PUBKEY(bio, rsa) != 1) {
        perror("Error writing public key to BIO");
        BIO_free(bio);
        return NULL;
    }

    char *buffer;
    long length = BIO_get_mem_data(bio, &buffer);

    char *result = malloc(length + 1);
    if (result == NULL) {
        perror("Error allocating memory for public key string");
        BIO_free(bio);
        return NULL;
    }

    memcpy(result, buffer, length);
    result[length] = '\0';

    BIO_free(bio);
    return result;
}

#endif //SECTRANS_RSA_H
