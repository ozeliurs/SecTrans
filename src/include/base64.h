//
// Created by Maxime BILLY on 08/01/2024.
//

#ifndef SECTRANS_BASE64_H
#define SECTRANS_BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char *base64_decode(const char *encoded_data) {
    BIO *bio, *b64;
    size_t len = strlen(encoded_data);
    char *decoded_data = (char *)malloc(len);  // Allocate memory for the decoded data
    if (!decoded_data) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    b64 = BIO_new(BIO_f_base64());  // Create a base64 filter
    bio = BIO_new_mem_buf(encoded_data, -1);  // Create a memory buffer BIO

    // Link the BIOs
    bio = BIO_push(b64, bio);

    // Decode the data
    BIO_read(bio, decoded_data, len);

    // Cleanup
    BIO_free_all(bio);

    return decoded_data;
}

char *base64_encode(const unsigned char *input, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    // Create a base64 filter/sink BIO
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    // Write the data to the BIO
    BIO_write(bio, input, length);
    BIO_flush(bio);

    // Get the pointer to the BIO's memory buffer
    BIO_get_mem_ptr(bio, &bufferPtr);

    // Allocate memory for the base64 encoded string and null terminate it
    char *encodedMsg = (char *)malloc(bufferPtr->length + 1);
    memcpy(encodedMsg, bufferPtr->data, bufferPtr->length);
    encodedMsg[bufferPtr->length] = '\0';

    // Clean up
    BIO_free_all(bio);

    return encodedMsg;
}

#endif //SECTRANS_BASE64_H
