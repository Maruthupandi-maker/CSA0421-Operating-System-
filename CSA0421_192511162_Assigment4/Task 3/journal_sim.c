#include <stdio.h>

int main(void) {
    printf("=== EXT4 JOURNALING CONSISTENCY & CRASH RESILIENCE MODEL ===\n\n");
    printf("Journaling Mode  | Data Written to  | Metadata Written | Crash Window Risk\n");
    printf("-----------------+------------------+------------------+--------------------------\n");
    printf("journal          | Journal First    | Journal First    | Zero data/metadata loss\n");
    printf("ordered (Default)| Filesystem First | Journal First    | No metadata corruption\n");
    printf("writeback        | Asynchronous     | Journal First    | Stale data in file risk\n\n");

    printf("[Evaluation for Database Server]:\n");
    printf("Recommendation: ext4 with 'ordered' mode (or XFS with pre-allocation).\n");
    printf("COW file systems (Btrfs/ZFS) suffer severe write amplification during random 4 KB database updates,\n");
    printf("because updating a single database page requires writing a new block and updating the entire tree upward.\n");
    return 0;
}
