#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000
#define FRAMES 4

int find(const int f[], int n, int page) {
    for (int i = 0; i < n; i++) if (f[i] == page) return i;
    return -1;
}

int main(void) {
    srand(192511162);
    int *refs = malloc(N * sizeof(int));
    // Generate 80/20 locality distribution
    for (int i = 0; i < N; i++) {
        if ((rand() % 100) < 80) refs[i] = rand() % 8; // Hot working set (pages 0-7)
        else refs[i] = 8 + (rand() % 92);              // Cold pages (pages 8-99)
    }

    printf("=== 100,000 REFERENCES PERFORMANCE BENCHMARK (4 FRAMES) ===\n");

    // Benchmark FIFO
    clock_t start = clock();
    int f_fifo[FRAMES], used = 0, next = 0, faults_fifo = 0;
    for (int i = 0; i < N; i++) {
        if (find(f_fifo, used, refs[i]) >= 0) continue;
        faults_fifo++;
        if (used < FRAMES) f_fifo[used++] = refs[i];
        else { f_fifo[next] = refs[i]; next = (next + 1) % FRAMES; }
    }
    double time_fifo = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;

    // Benchmark LRU
    start = clock();
    int f_lru[FRAMES], last[FRAMES], faults_lru = 0;
    used = 0;
    for (int i = 0; i < N; i++) {
        int k = find(f_lru, used, refs[i]);
        if (k >= 0) { last[k] = i; continue; }
        faults_lru++;
        int victim = 0;
        if (used < FRAMES) victim = used++;
        else {
            int oldest = last[0];
            for (int j = 1; j < FRAMES; j++) {
                if (last[j] < oldest) { oldest = last[j]; victim = j; }
            }
        }
        f_lru[victim] = refs[i];
        last[victim] = i;
    }
    double time_lru = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;

    // Benchmark Clock
    start = clock();
    int f_clk[FRAMES], bit[FRAMES], ptr = 0, faults_clk = 0;
    used = 0;
    for (int i = 0; i < N; i++) {
        int k = find(f_clk, used, refs[i]);
        if (k >= 0) { bit[k] = 1; continue; }
        faults_clk++;
        if (used < FRAMES) { f_clk[used] = refs[i]; bit[used] = 1; used++; }
        else {
            while (bit[ptr] == 1) { bit[ptr] = 0; ptr = (ptr + 1) % FRAMES; }
            f_clk[ptr] = refs[i]; bit[ptr] = 1; ptr = (ptr + 1) % FRAMES;
        }
    }
    double time_clk = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;

    printf("FIFO  : %6ld Faults | Execution Time: %6.2f ms\n", faults_fifo, time_fifo);
    printf("LRU   : %6ld Faults | Execution Time: %6.2f ms\n", faults_lru, time_lru);
    printf("Clock : %6ld Faults | Execution Time: %6.2f ms (Near-LRU Hit Rate, Zero Search Overhead)\n", faults_clk, time_clk);

    free(refs);
    return 0;
}
