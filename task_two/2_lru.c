#include <stdio.h>

int main() {
    int apps[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = 12;
    int memory[3] = {-1, -1, -1};
    int last_used[3] = {-1, -1, -1};   // tracks when each slot was last touched
    int hits = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        int app = apps[i];
        int found = -1;

        for (int j = 0; j < 3; j++) {
            if (memory[j] == app) found = j;
        }

        if (found != -1) {
            printf("App %d: already open (HIT)\n", app);
            hits++;
            last_used[found] = i;
        } else {
            printf("App %d: opening, closes least recently used app (FAULT)\n", app);
            faults++;

            int target = -1;
            for (int j = 0; j < 3; j++) {
                if (memory[j] == -1) { target = j; break; }  // empty slot first
            }
            if (target == -1) {
                target = 0;
                for (int j = 1; j < 3; j++) {
                    if (last_used[j] < last_used[target]) target = j;
                }
            }

            memory[target] = app;
            last_used[target] = i;
        }
    }

    printf("\nHits: %d, Faults: %d\n", hits, faults);
    return 0;
}
