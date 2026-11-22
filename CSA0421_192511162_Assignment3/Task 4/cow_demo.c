#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_rss(const char *label) {
    FILE *fp = fopen("/proc/self/statm", "r");
    if (fp) {
        long size, resident, share;
        if (fscanf(fp, "%ld %ld %ld", &size, &resident, &share) == 3) {
            printf("[%s] Resident Set: %ld KB | Shared Pages: %ld KB\n", 
                   label, resident * 4, share * 4);
        }
        fclose(fp);
    }
}

int main(void) {
    size_t size = 64 * 1024 * 1024; // 64 MB
    char *data = malloc(size);
    memset(data, 'A', size); // Pre-fault memory

    printf("=== COPY-ON-WRITE (COW) DEMONSTRATION WITH fork() ===\n");
    print_rss("Parent before fork");

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        print_rss("Child immediately after fork (Read-Only Shared)");
        printf("[*] Child modifying 32 MB of memory...\n");
        memset(data, 'B', size / 2); // Triggers Copy-on-Write page duplication
        print_rss("Child after write modification (Private Dirty Pages)");
        _exit(0);
    } else {
        wait(NULL);
        print_rss("Parent after child exit");
    }
    free(data);
    return 0;
}
