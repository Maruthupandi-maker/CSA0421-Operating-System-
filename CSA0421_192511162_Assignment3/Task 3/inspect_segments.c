#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_initialized = 42;
int global_uninitialized;

int main(void) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps | grep -E 'inspect_seg|stack|heap'", getpid());
    printf("=== LINUX MEMORY SEGMENTS (/proc/self/maps) ===\n");
    printf("Process PID: %d\n", getpid());
    fflush(stdout);
    system(cmd);
    return 0;
}
