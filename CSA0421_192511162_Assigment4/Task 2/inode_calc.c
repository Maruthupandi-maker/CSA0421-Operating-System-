#include <stdio.h>

int main(void) {
    printf("=== TASK 2: FILE ALLOCATION COST & INODE SIZING CALCULATIONS ===\n\n");
    printf("[1] 4 GB File (4 KB Blocks -> 1,048,576 Blocks) Disk Reads to Reach Last Block:\n");
    printf("    Contiguous Allocation : 1 Read (Direct index calculation from start block)\n");
    printf("    Linked Allocation     : 1,048,576 Reads (Must traverse all intermediate pointers)\n");
    printf("    Indexed Allocation    : 3 Reads (Double-indirect block -> Indirect block -> Data block)\n\n");

    printf("[2] Unix Inode Maximum File Size (4 KB Blocks, 4-Byte Block Addresses):\n");
    long long ptr_per_blk = 4096 / 4; // 1024 pointers per block
    long long direct_bytes = 12 * 4096;
    long long single_bytes = ptr_per_blk * 4096;
    long long double_bytes = ptr_per_blk * ptr_per_blk * 4096;
    long long triple_bytes = ptr_per_blk * ptr_per_blk * ptr_per_blk * 4096;
    long long total_bytes = direct_bytes + single_bytes + double_bytes + triple_bytes;

    printf("    Direct Pointers (12)      : %12lld Bytes (48 KB)\n", direct_bytes);
    printf("    Single-Indirect (1)       : %12lld Bytes (4 MB)\n", single_bytes);
    printf("    Double-Indirect (1)       : %12lld Bytes (4 GB)\n", double_bytes);
    printf("    Triple-Indirect (1)       : %12lld Bytes (4 TB)\n", triple_bytes);
    printf("    --------------------------------------------------------\n");
    printf("    TOTAL MAXIMUM FILE SIZE   : %12lld Bytes (~ 4.004 TB)\n\n", total_bytes);

    printf("[3] Free-Space Management for 4 TB Disk with 4 KB Blocks (2^30 Blocks):\n");
    printf("    Bit Vector Size           : 2^30 bits = 134,217,728 Bytes (128 MB RAM)\n");
    printf("    Counting Method           : ~ 2.4 MB (Storing [start_block, count] runs)\n");
    return 0;
}
