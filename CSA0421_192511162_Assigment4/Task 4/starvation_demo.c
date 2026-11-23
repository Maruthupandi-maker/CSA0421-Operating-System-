#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== DISK SCHEDULING: SSTF STARVATION INVESTIGATION ===\n\n");
    printf("Initial Request Queue: Head at 53. Distant target: Cylinder 183.\n");
    printf("[*] Simulating continuous arrival of new requests near cylinder 60 (58, 62, 59, 61, 60...)\n");
    
    int current_head = 53;
    int target_request = 183;
    int incoming_near_60[] = {58, 62, 59, 61, 60, 63, 57, 64, 59, 62};
    
    for (int t = 1; t <= 10; t++) {
        int next_req = incoming_near_60[t - 1];
        int dist_to_local = abs(next_req - current_head);
        int dist_to_target = abs(target_request - current_head);
        printf("Time %2d ms: Head at %2d | New Req %2d (dist=%2d) vs Target %d (dist=%3d) -> Servicing %2d\n",
               t, current_head, next_req, dist_to_local, target_request, dist_to_target, next_req);
        current_head = next_req;
    }
    printf("\n[RESULT]: Request at cylinder 183 suffers PERMANENT STARVATION under SSTF!\n");
    printf("Under C-SCAN / SCAN, the head moves unidirectionally across all cylinders,\n");
    printf("guaranteeing bounded maximum waiting time and complete starvation immunity.\n");
    return 0;
}
