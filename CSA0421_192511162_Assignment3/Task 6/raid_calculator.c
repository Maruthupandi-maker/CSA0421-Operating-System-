#include <stdio.h>
#include <math.h>

int main(void) {
    int N = 6;              // 6 Disks
    double S = 4.0;         // 4 TB per disk
    double p = 0.02;        // Annual disk failure probability = 2%

    printf("=== HOSPITAL RECORDS STORAGE: RAID ARCHITECTURAL MODELING ===\n");
    printf("Disk Array: 6 Disks of 4 TB Each (Raw Capacity = 24.0 TB)\n");
    printf("Assumed Single-Disk Annual Failure Rate (p): %.1f%%\n\n", p * 100);

    // Usable Capacities
    double cap_raid0  = N * S;                  // 24 TB
    double cap_raid1  = (N / 2.0) * S;          // 12 TB (Mirrored pairs)
    double cap_raid5  = (N - 1.0) * S;          // 20 TB (Single distributed parity)
    double cap_raid6  = (N - 2.0) * S;          // 16 TB (Dual distributed parity)
    double cap_raid10 = (N / 2.0) * S;          // 12 TB (Striping across mirrors)

    printf("[1] Usable Storage Capacities:\n");
    printf("RAID 0  : %4.1f TB (100.0%% efficiency | 0 Fault Tolerance)\n", cap_raid0);
    printf("RAID 1  : %4.1f TB ( 50.0%% efficiency | Survived: 1 disk per mirror pair)\n", cap_raid1);
    printf("RAID 5  : %4.1f TB ( 83.3%% efficiency | Survived: exactly 1 disk failure)\n", cap_raid5);
    printf("RAID 6  : %4.1f TB ( 66.7%% efficiency | Survived: any 2 disk failures)\n", cap_raid6);
    printf("RAID 10 : %4.1f TB ( 50.0%% efficiency | Survived: up to 3 disks, 1 per pair)\n\n", cap_raid10);

    // Reliability & Probability of Data Loss
    // RAID 0: Loss if ANY disk fails: P = 1 - (1 - p)^6
    double p_loss_0 = 1.0 - pow(1.0 - p, N);

    // RAID 5: Loss if 2 or more disks fail: Sum_{k=2}^6 C(6,k) * p^k * (1-p)^(6-k)
    // C(6,2) = 15 => ~ 15 * p^2 * (1-p)^4
    double p_loss_5 = 15 * pow(p, 2) * pow(1.0 - p, 4) + 20 * pow(p, 3) * pow(1.0 - p, 3);

    // RAID 6: Loss if 3 or more disks fail: C(6,3) * p^3 => ~ 20 * p^3
    double p_loss_6 = 20 * pow(p, 3) * pow(1.0 - p, 3);

    // RAID 10: Loss if BOTH disks in the same mirror pair fail (3 pairs)
    // Prob a pair fails = p^2. Prob at least one pair fails = 1 - (1 - p^2)^3 ~ 3 * p^2
    double p_loss_10 = 1.0 - pow(1.0 - (p * p), N / 2);

    printf("[2] Probability of Catastrophic Data Loss (Over 1 Year):\n");
    printf("RAID 0  : %7.4f%% (Extremely Dangerous for Medical Records)\n", p_loss_0 * 100);
    printf("RAID 5  : %7.4f%% (Risk of secondary failure during rebuild!)\n", p_loss_5 * 100);
    printf("RAID 6  : %7.4f%% (Dual Parity resilience)\n", p_loss_6 * 100);
    printf("RAID 10 : %7.4f%% (Optimal resilience & fastest rebuild)\n", p_loss_10 * 100);

    return 0;
}
