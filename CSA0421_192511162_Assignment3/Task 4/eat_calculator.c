#include <stdio.h>

int main(void) {
    double t_mem = 100.0;         // 100 nanoseconds = 100 * 10^-9 s
    double t_fault = 8000000.0;   // 8 milliseconds = 8,000,000 ns

    printf("=== DEMAND PAGING EFFECTIVE ACCESS TIME (EAT) ===\n");
    printf("Memory Access Time (T_mem) : 100 ns\n");
    printf("Page Fault Service (T_fault): 8,000,000 ns (8 ms)\n\n");

    double rates[] = {1.0 / 1000.0, 1.0 / 100000.0, 1.0 / 1000000.0};
    const char *labels[] = {"1 in 1,000   ", "1 in 100,000 ", "1 in 1,000,000"};

    for (int i = 0; i < 3; i++) {
        double p = rates[i];
        double eat = (1.0 - p) * t_mem + p * t_fault;
        printf("Fault Rate p = %s -> EAT = %10.2f ns (Slowdown: %6.1fx)\n", 
               labels[i], eat, eat / t_mem);
    }

    // Maximum acceptable page-fault rate for 10% slowdown (EAT <= 110 ns)
    // 110 = 100 + p * (8,000,000 - 100) => p = 10 / 7,999,900
    double max_p = 10.0 / (t_fault - t_mem);
    printf("\n[Criterion] Maximum Acceptable Fault Rate for 10%% Slowdown:\n");
    printf("p <= %.8f (~ 1 fault in every %.0f memory accesses!)\n", max_p, 1.0 / max_p);
    return 0;
}
