#include <stdio.h>

int main(void) {
    printf("=== TASK 5: DISTRIBUTED & CLOUD STORAGE ARCHITECTURAL COMPARISON ===\n\n");
    printf("Storage Type    | Consistency   | Availability  | Latency / Perf  | Cost / TB / Mo\n");
    printf("----------------+---------------+---------------+-----------------+-----------------\n");
    printf("Network FS (NFS)| Strong (POSIX)| Single Pt Fail| Low (&lt;1 ms LAN) | High (Server NAS)\n");
    printf("Ceph / HDFS     | Strong/Eventual 99.999% (3x)   | Medium (Cluster)| Moderate (On-prem)\n");
    printf("Cloud S3 / GCS  | Strong Read/Wr| 99.999999999% | Variable (WAN)  | Low ($0.020/GB)\n\n");

    printf("[Replication & CAP Theorem Trade-off]:\n");
    printf("HDFS 3-way replication pipeline: Client -> DataNode A -> DataNode B -> DataNode C.\n");
    printf("Strong consistency requires synchronous ack from all replicas (higher write latency).\n");
    printf("Eventual consistency acks primary and replicates asynchronously (higher write throughput, risk of stale reads).\n");
    return 0;
}
