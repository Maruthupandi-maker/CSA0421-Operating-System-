#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Simulates 100 random student processes and calculates internal fragmentation
int main(void) {
    srand(192511162);
    int num_proc = 100;
    long long total_frag_1k = 0;
    long long total_frag_4k = 0;
    long long total_frag_2m = 0;

    for (int i = 0; i < num_proc; i++) {
        // Process size uniformly distributed between 10 KB and 20 MB
        long long sz = 10240 + (rand() % (20 * 1024 * 1024));
        
        long long rem1 = sz % 1024;
        total_frag_1k += (rem1 == 0) ? 0 : (1024 - rem1);

        long long rem4 = sz % 4096;
        total_frag_4k += (rem4 == 0) ? 0 : (4096 - rem4);

        long long rem2m = sz % (2 * 1024 * 1024);
        total_frag_2m += (rem2m == 0) ? 0 : ((2 * 1024 * 1024) - rem2m);
    }

    printf("=== INTERNAL FRAGMENTATION FOR 100 RANDOM STUDENT PROCESSES ===\n");
    printf("Page Size  1 KB : Total Waste = %8.2f KB | Avg Waste/Proc = %6.2f Bytes\n", 
           total_frag_1k / 1024.0, (double)total_frag_1k / num_proc);
    printf("Page Size  4 KB : Total Waste = %8.2f KB | Avg Waste/Proc = %6.2f Bytes\n", 
           total_frag_4k / 1024.0, (double)total_frag_4k / num_proc);
    printf("Page Size  2 MB : Total Waste = %8.2f MB | Avg Waste/Proc = %6.2f KB\n", 
           total_frag_2m / (1024.0 * 1024.0), (double)total_frag_2m / (num_proc * 1024.0));

    printf("\n=== EFFECTIVE ACCESS TIME (EAT) CALCULATIONS ===\n");
    printf("Parameters: Memory Access Time = 100 ns, TLB Lookup Time = 20 ns\n");
    double hit_ratios[] = {0.80, 0.95, 0.99};
    for (int j = 0; j < 3; j++) {
        double alpha = hit_ratios[j];
        // Single level paging: Hit = TLB + Mem (120 ns), Miss = TLB + 2*Mem (220 ns)
        double eat = alpha * (20 + 100) + (1.0 - alpha) * (20 + 100 + 100);
        printf("TLB Hit Ratio: %4.1f%% -> EAT = %6.2f ns\n", alpha * 100, eat);
    }
    return 0;
}
