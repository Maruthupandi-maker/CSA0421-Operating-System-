#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segfault_handler(int sig) {
    printf("\n[!] CAUGHT SIGNAL %d (SIGSEGV) - Operating System Protection Unit Invoked!\n", sig);
    printf("[!] OS Action: MMU signaled CPU fault -> OS kernel looked up VMA -> Access invalid.\n");
    printf("[!] OS terminates violation process or invokes registered handler to prevent RAM corruption.\n");
    exit(139);
}

int main(void) {
    signal(SIGSEGV, segfault_handler);
    printf("=== TRIGGERING DELIBERATE SEGMENTATION FAULT ===\n");
    printf("[*] Attempting to write into Read-Only text segment / NULL pointer...\n");

    int *bad_ptr = NULL;
    *bad_ptr = 192511162; // Deliberate invalid memory access
    return 0;
}
