#ifndef ENCRYPT_H
#define ENCRYPT_H

// Core banking cryptographic module interface
void encrypt_data(const char *input, char *output, int key);
void decrypt_data(const char *input, char *output, int key);
const char* get_cipher_version(void);

#endif
