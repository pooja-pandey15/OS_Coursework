/*
 * paging_sim.c
 * Task 2: Memory Management Simulation
 * Stage 2 - LRU page replacement algorithm
 *
 */

#include <stdio.h>

#define NUM_FRAMES 3
#define REFERENCE_LENGTH 12

int reference_string[REFERENCE_LENGTH] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

void print_frames(int frames[], int count) {
    printf("Frames: [ ");
    for (int i = 0; i < count; i++) {
        if (frames[i] == -1)
            printf("_ ");
        else
            printf("%d ", frames[i]);
    }
    printf("]\n");
}

int is_in_frames(int frames[], int count, int page) {
    for (int i = 0; i < count; i++) {
        if (frames[i] == page) return 1;
    }
    return 0;
}

// Returns the index of the frame whose page was used LONGEST ago
// (i.e. has the smallest/oldest "last_used" timestamp) - this is the
// frame LRU will evict.
int find_lru_index(int last_used[], int count) {
    int lru_index = 0;
    for (int i = 1; i < count; i++) {
        if (last_used[i] < last_used[lru_index]) {
            lru_index = i;
        }
    }
    return lru_index;
}

// Given a page currently in the frames, find which frame index holds it.
int find_frame_of_page(int frames[], int count, int page) {
    for (int i = 0; i < count; i++) {
        if (frames[i] == page) return i;
    }
    return -1;
}

int main() {
    int frames[NUM_FRAMES];
    int last_used[NUM_FRAMES]; // tracks the "time" (request index) each frame's page was last touched

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;
    int page_hits = 0;

    printf("=== LRU Page Replacement Simulation ===\n");
    printf("Number of frames: %d\n\n", NUM_FRAMES);

    for (int i = 0; i < REFERENCE_LENGTH; i++) {
        int page = reference_string[i];
        printf("Request %2d: page %d -> ", i, page);

        if (is_in_frames(frames, NUM_FRAMES, page)) {
            printf("HIT   ");
            page_hits++;

            // Update this page's "last used" time to now, since it was just accessed again.
            int idx = find_frame_of_page(frames, NUM_FRAMES, page);
            last_used[idx] = i;

        } else {
            printf("FAULT ");
            page_faults++;

            // Find an empty frame first, if one exists
            int target_index = -1;
            for (int f = 0; f < NUM_FRAMES; f++) {
                if (frames[f] == -1) {
                    target_index = f;
                    break;
                }
            }

            // No empty frame found - evict the Least Recently Used page
            if (target_index == -1) {
                target_index = find_lru_index(last_used, NUM_FRAMES);
            }

            frames[target_index] = page;
            last_used[target_index] = i; // mark this frame as just used, at time i
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
