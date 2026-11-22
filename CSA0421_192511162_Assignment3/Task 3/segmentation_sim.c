#include <stdio.h>
#include <stdbool.h>

// Segment Table Entry: Base, Limit, Permissions
typedef struct {
    int segment_id;
    const char *name;
    unsigned int base;
    unsigned int limit;
    const char *permissions;
} SegmentEntry;

#define NUM_SEGMENTS 5

SegmentEntry segment_table[NUM_SEGMENTS] = {
    {0, "Code (Text)",   1400, 1000, "r-x (Shared)"},
    {1, "Data (Globals)", 6300,  400, "rw- (Private)"},
    {2, "Heap (Dynamic)", 4300,  600, "rw- (Private)"},
    {3, "Stack (Local)",  3200,  800, "rw- (Private, Downward)"},
    {4, "Shared Lib",     7500,  500, "r-x (Shared)"}
};

void translate(int seg, unsigned int offset) {
    if (seg < 0 || seg >= NUM_SEGMENTS) {
        printf("Logical (%d, %4u) -> TRAP: Invalid Segment ID!\n", seg, offset);
        return;
    }
    SegmentEntry e = segment_table[seg];
    if (offset >= e.limit) {
        printf("Logical (%d [%s], %4u) -> TRAP: SEGMENTATION FAULT (Offset %u >= Limit %u)\n",
               seg, e.name, offset, offset, e.limit);
    } else {
        unsigned int physical = e.base + offset;
        printf("Logical (%d [%s], %4u) -> Physical Address: %5u [Perms: %s]\n",
               seg, e.name, offset, physical, e.permissions);
    }
}

int main(void) {
    printf("=== SEGMENTATION TRANSLATION VERIFICATION (8 TEST ADDRESSES) ===\n");
    // 8 Hand-Calculated Addresses (including boundary checks and limit violations)
    translate(0, 0);     // Start of Code
    translate(0, 999);   // Valid end of Code
    translate(0, 1000);  // Breach Code limit
    translate(1, 150);   // Valid Data offset
    translate(2, 600);   // Breach Heap limit
    translate(3, 400);   // Valid Stack offset
    translate(4, 250);   // Valid Shared Lib offset
    translate(5, 50);    // Out of range segment ID
    return 0;
}
