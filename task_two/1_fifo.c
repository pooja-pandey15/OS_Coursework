#include <stdio.h>

int main() {
    int apps[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};  // apps being opened, in order
    int n = 12;
    int memory[3] = {-1, -1, -1};   // phone can only hold 3 apps at once
    int oldest = 0;
    int hits = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        int app = apps[i];
        int found = 0;

        for (int j = 0; j < 3; j++) {
            if (memory[j] == app) found = 1;
        }

        if (found) {
            printf("App %d: already open (HIT)\n", app);
            hits++;
        } else {
            printf("App %d: opening, closes oldest app (FAULT)\n", app);
            memory[oldest] = app;
            oldest = (oldest + 1) % 3;
            faults++;
        }
    }

    printf("\nHits: %d, Faults: %d\n", hits, faults);
    return 0;
}
