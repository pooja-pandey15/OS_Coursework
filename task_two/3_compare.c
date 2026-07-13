#include <stdio.h>

int apps[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
int n = 12;

void run_fifo(int *hits, int *faults) {
    int memory[3] = {-1, -1, -1};
    int oldest = 0;
    *hits = 0;
    *faults = 0;

    for (int i = 0; i < n; i++) {
        int app = apps[i];
        int found = 0;
        for (int j = 0; j < 3; j++) {
            if (memory[j] == app) found = 1;
        }
        if (found) {
            (*hits)++;
        } else {
            memory[oldest] = app;
            oldest = (oldest + 1) % 3;
            (*faults)++;
        }
    }
}

void run_lru(int *hits, int *faults) {
    int memory[3] = {-1, -1, -1};
    int last_used[3] = {-1, -1, -1};
    *hits = 0;
    *faults = 0;

    for (int i = 0; i < n; i++) {
        int app = apps[i];
        int found = -1;
        for (int j = 0; j < 3; j++) {
            if (memory[j] == app) found = j;
        }
        if (found != -1) {
            (*hits)++;
            last_used[found] = i;
        } else {
            (*faults)++;
            int target = -1;
            for (int j = 0; j < 3; j++) {
                if (memory[j] == -1) { target = j; break; }
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
}

int main() {
    int fifo_hits, fifo_faults, lru_hits, lru_faults;

    run_fifo(&fifo_hits, &fifo_faults);
    run_lru(&lru_hits, &lru_faults);

    printf("FIFO -> Hits: %d, Faults: %d\n", fifo_hits, fifo_faults);
    printf("LRU  -> Hits: %d, Faults: %d\n", lru_hits, lru_faults);

    if (fifo_hits > lru_hits) {
        printf("\nFIFO did better this time.\n");
    } else if (lru_hits > fifo_hits) {
        printf("\nLRU did better this time.\n");
    } else {
        printf("\nBoth did the same.\n");
    }

    return 0;
}
