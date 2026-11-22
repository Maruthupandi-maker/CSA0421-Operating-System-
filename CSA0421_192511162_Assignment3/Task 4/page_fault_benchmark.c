#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#define NUM_PAGES 65536 // 65,536 * 4096 = 256 MB test buffer
#define PAGE_SZ 4096

int main(void) {
    struct rusage usage_start, usage_end;
    struct timeval t_start, t_end;

    printf("=== VIRTUAL MEMORY ACCESS BENCHMARK (256 MB BUFFER) ===\n");
    char *buffer = (char*)malloc((size_t)NUM_PAGES * PAGE_SZ);
    if (!buffer) { perror("malloc failed"); return 1; }

    // Test 1: Sequential Access (High Spatial Locality)
    getrusage(RUSAGE_SELF, &usage_start);
    gettimeofday(&t_start, NULL);

    for (int i = 0; i < NUM_PAGES; i++) {
        buffer[i * PAGE_SZ] = (char)(i & 0xFF);
    }

    gettimeofday(&t_end, NULL);
    getrusage(RUSAGE_SELF, &usage_end);

    double seq_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0 + (t_end.tv_usec - t_start.tv_usec) / 1000.0;
    long seq_faults = usage_end.ru_minflt - usage_start.ru_minflt;
    printf("[Sequential Access] Time: %6.2f ms | Minor Page Faults: %ld\n", seq_time, seq_faults);

    // Test 2: Random Stride Access (Zero Locality)
    getrusage(RUSAGE_SELF, &usage_start);
    gettimeofday(&t_start, NULL);

    for (int i = 0; i < NUM_PAGES; i++) {
        // Pseudo-random pseudo-permutation index
        size_t idx = (size_t)((i * 32749 + 17) % NUM_PAGES);
        buffer[idx * PAGE_SZ] += 1;
    }

    gettimeofday(&t_end, NULL);
    getrusage(RUSAGE_SELF, &usage_end);

    double rand_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0 + (t_end.tv_usec - t_start.tv_usec) / 1000.0;
    long rand_faults = usage_end.ru_minflt - usage_start.ru_minflt;
    printf("[Random Access    ] Time: %6.2f ms | Minor Page Faults: %ld (Cache Miss Penalty)\n", rand_time, rand_faults);

    free(buffer);
    return 0;
}
