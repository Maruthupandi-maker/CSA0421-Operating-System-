#include "encrypt.h"
#include <string.h>

static const char *VERSION = "v1.2.0-SECURE-PATCHED";

void encrypt_data(const char *input, char *output, int key) {
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        output[i] = (char)(input[i] ^ (key + (i % 7)));
    }
    output[len] = '\0';
}

void decrypt_data(const char *input, char *output, int key) {
    encrypt_data(input, output, key); // Symmetric XOR cipher
}

const char* get_cipher_version(void) {
    return VERSION;
}
