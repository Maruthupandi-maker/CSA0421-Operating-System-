#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>

#define LOOP_ITERATIONS 100000
#define BUFFER_SIZE (16 * 1024 * 1024) // 16 MB critical control buffer

double run_control_loop(char *buf) {
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for (int i = 0; i < LOOP_ITERATIONS; i++) {
        size_t idx = (size_t)((i * 4096) % BUFFER_SIZE);
        buf[idx] = (char)(buf[idx] + 1);
    }
    gettimeofday(&t2, NULL);
    return (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
}

int main(int argc, char *argv[]) {
    int enable_lock = (argc > 1 && strcmp(argv[1], "--lock") == 0);
    printf("=== SMART FACTORY EDGE CONTROLLER MEMORY VERIFICATION ===\n");
    printf("Mode: %s\n", enable_lock ? "HARD REAL-TIME (mlockall PINNED)" : "STANDARD (UNLOCKED / DEMAND PAGED)");

    char *control_buffer = malloc(BUFFER_SIZE);
    if (!control_buffer) { perror("malloc"); return 1; }

    if (enable_lock) {
        // Lock all current and future process memory into physical RAM
        if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
            perror("mlockall failed (requires CAP_IPC_LOCK)");
            return 1;
        }
        // Explicitly pre-fault entire buffer to eliminate cold start traps
        memset(control_buffer, 0, BUFFER_SIZE);
        printf("[+] Memory pages pinned and pre-faulted in RAM. Zero page faults guaranteed.\n");
    }

    printf("[*] Executing time-critical robotic feedback loop (%d cycles)...\n", LOOP_ITERATIONS);
    double latency = run_control_loop(control_buffer);
    printf("[Result] Total Execution Delay: %6.2f ms | Avg Latency/Cycle: %6.3f microseconds\n", 
           latency, (latency * 1000.0) / LOOP_ITERATIONS);

    if (enable_lock) {
        munlockall();
    }
    free(control_buffer);
    return 0;
}
