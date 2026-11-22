#include <stdio.h>
#include <string.h>
#include "encrypt.h"

// Dynamically linked banking module
int main(void) {
    char plain[] = "ACCOUNT:8829-1092-4412;AMOUNT:450000.00";
    char cipher[128];
    char restored[128];

    printf("=== BANKING SYSTEM (DYNAMIC LINKING) ===\n");
    printf("Encryption Library Version: %s\n", get_cipher_version());
    printf("Original Data : %s\n", plain);

    encrypt_data(plain, cipher, 42);
    printf("Encrypted Data: [CIPHERTEXT BYTES]\n");

    decrypt_data(cipher, restored, 42);
    printf("Decrypted Data: %s\n", restored);

    return 0;
}
