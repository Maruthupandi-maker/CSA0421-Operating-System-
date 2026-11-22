#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Inspects virtual memory map via /proc/self/maps
int main(void) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps | head -n 25", getpid());
    printf("=== PROCESS VIRTUAL ADDRESS MAP (/proc/self/maps) ===\n");
    printf("PID: %d\n", getpid());
    fflush(stdout);
    system(cmd);
    return 0;
}
