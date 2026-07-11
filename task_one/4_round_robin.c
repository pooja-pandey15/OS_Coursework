#include <stdio.h>

int main() {
    int jobs = 9;          // total jobs in queue
    int printers = 3;      // number of printers taking turns
    int turn = 0;
    int done = 0;

    printf("Starting round robin with %d printers and %d jobs\n\n", printers, jobs);

    while (done < jobs) {
        printf("Printer %d takes job %d\n", turn, done);
        done++;
        turn = (turn + 1) % printers;   // move to next printer, wrap around
    }

    printf("\nAll %d jobs done\n", jobs);
    return 0;
}
