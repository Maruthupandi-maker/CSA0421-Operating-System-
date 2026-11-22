#include <stdio.h>
#include <stdbool.h>

typedef struct {
    const char *name;
    int memory_mb;
    bool is_realtime;
    bool locked;
    int max_acceptable_latency_us;
} TaskSpec;

int main(void) {
    printf("=== STAGE 3: MULTI-TASK MEMORY CONTROLLER SIMULATION ===\n");
    printf("Platform: 2048 MB Physical RAM | Swap Disk: NONE\n\n");

    TaskSpec tasks[4] = {
        {"Task 1: Real-Time Control",   128, true,  true,     50},
        {"Task 2: Machine Learning",   1536, false, false, 200000},
        {"Task 3: Logging & Telemetry",  128, false, false,  50000},
        {"Task 4: Future Expansion",    500, false, false,  50000}
    };

    int allocated_ram = 0;
    for (int i = 0; i < 3; i++) {
        allocated_ram += tasks[i].memory_mb;
        printf("[Active] %-28s: %4d MB | Locked: %-5s | Timing: <= %d us\n", 
               tasks[i].name, tasks[i].memory_mb, tasks[i].locked ? "YES" : "NO", tasks[i].max_acceptable_latency_us);
    }
    printf("Total Current Memory Footprint: %d MB / 2048 MB (Headroom = %d MB)\n\n", 
           allocated_ram, 2048 - allocated_ram);

    printf("--- Stage 4: Stress Test (Simulating Task 4 [500 MB] Addition) ---\n");
    int projected_ram = allocated_ram + tasks[3].memory_mb;
    printf("Projected RAM Demand: %d MB / 2048 MB -> DEFICIT: %d MB!\n", projected_ram, projected_ram - 2048);
    printf("[!] OS Action: With swap=0, kernel Out-Of-Memory (OOM) killer would trigger!\n");
    printf("[Solution Implemented]:\n");
    printf(" 1. Protect Task 1: oom_score_adj = -1000 (NEVER kill real-time controller).\n");
    printf(" 2. Restrict ML Task via cgroups v2 memory.high = 1200 MB (quantized dynamic batching).\n");
    printf(" 3. Memory-map weights as MAP_SHARED read-only (page cache eviction without swap).\n");

    return 0;
}
