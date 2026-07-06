/*
 * paging_sim.c
 * Task 2: Memory Management Simulation
 * Stage 1 - FIFO page replacement algorithm
 *
 */

#include <stdio.h>

#define NUM_FRAMES 3        // number of physical memory frames available
#define REFERENCE_LENGTH 12 // how many page requests we will simulate

// This is our "reference string" - the sequence of pages the program requests,
// in order. This particular pattern is a classic textbook example used to
// demonstrate paging algorithms.
int reference_string[REFERENCE_LENGTH] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

void print_frames(int frames[], int count) {
    printf("Frames: [ ");
    for (int i = 0; i < count; i++) {
        if (frames[i] == -1)
            printf("_ ");   // -1 means the frame is currently empty
        else
            printf("%d ", frames[i]);
    }
    printf("]\n");
}

// Checks if 'page' is already present in the frames array. Returns 1 if found, 0 if not.
int is_in_frames(int frames[], int count, int page) {
    for (int i = 0; i < count; i++) {
        if (frames[i] == page) return 1;
    }
    return 0;
}

int main() {
    int frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) frames[i] = -1; // -1 = empty frame

    int oldest_index = 0;   // tracks which frame to replace next (FIFO pointer)
    int page_faults = 0;
    int page_hits = 0;

    printf("=== FIFO Page Replacement Simulation ===\n");
    printf("Number of frames: %d\n\n", NUM_FRAMES);

    for (int i = 0; i < REFERENCE_LENGTH; i++) {
        int page = reference_string[i];
        printf("Request %2d: page %d -> ", i, page);

        if (is_in_frames(frames, NUM_FRAMES, page)) {
            // Page already in memory - no work needed
            printf("HIT   ");
            page_hits++;
        } else {
            // Page not in memory - this is a page fault
            printf("FAULT ");
            page_faults++;

            // Place the new page into the oldest slot (FIFO eviction)
            frames[oldest_index] = page;
            oldest_index = (oldest_index + 1) % NUM_FRAMES; // move pointer forward, wrapping around
        }

        print_frames(frames, NUM_FRAMES);
    }

    printf("\n=== Summary ===\n");
    printf("Total requests: %d\n", REFERENCE_LENGTH);
    printf("Page hits:      %d\n", page_hits);
    printf("Page faults:    %d\n", page_faults);
    printf("Hit ratio:      %.2f%%\n", (page_hits * 100.0) / REFERENCE_LENGTH);
    printf("Miss ratio:     %.2f%%\n", (page_faults * 100.0) / REFERENCE_LENGTH);

    return 0;
}
