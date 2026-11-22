#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*encrypt_fn)(const char*, char*, int);
typedef void (*decrypt_fn)(const char*, char*, int);
typedef const char* (*version_fn)(void);

// On-demand runtime loading using dlopen() and dlsym()
int main(void) {
    printf("=== BANKING SYSTEM (RUNTIME DLOPEN) ===\n");
    printf("[*] Starting main transaction process without encryption library in RAM...\n");

    // Load library strictly on-demand
    void *handle = dlopen("./libencrypt.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "[-] Critical Error: Failed to load encryption library: %s\n", dlerror());
        fprintf(stderr, "[-] Fallback: Flagging transaction for deferred offline security verification.\n");
        return 1;
    }

    encrypt_fn encrypt_data = (encrypt_fn)dlsym(handle, "encrypt_data");
    decrypt_fn decrypt_data = (decrypt_fn)dlsym(handle, "decrypt_data");
    version_fn get_cipher_version = (version_fn)dlsym(handle, "get_cipher_version");

    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "[-] Symbol resolution error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    printf("[+] Successfully resolved cryptographic symbols from %s\n", get_cipher_version());
    char plain[] = "ACCOUNT:8829-1092-4412;AMOUNT:450000.00";
    char cipher[128];
    char restored[128];

    encrypt_data(plain, cipher, 42);
    printf("[+] Data encrypted successfully.\n");

    decrypt_data(cipher, restored, 42);
    printf("[+] Decrypted Payload: %s\n", restored);

    dlclose(handle);
    printf("[*] Cryptographic library unloaded. Memory freed.\n");
    return 0;
}
