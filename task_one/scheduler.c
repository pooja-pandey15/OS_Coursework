/*
 * scheduler.c
 * Task 1: Process Management and Threading
 * Stage 4 - Round-robin scheduler simulation
 */

#include <stdio.h>

#define NUM_PROCESSES 4
#define QUANTUM 3   // each process gets 3 units of CPU time per turn

typedef struct {
    int pid;              // process ID
    int burst_time;       // total CPU time this process still needs
    int total_burst_time; // original burst time, kept for reporting
    int waiting_time;
    int turnaround_time;
} Process;

int main() {
    Process processes[NUM_PROCESSES] = {
        {1, 10, 10, 0, 0},
        {2, 5,  5,  0, 0},
        {3, 8,  8,  0, 0},
        {4, 3,  3,  0, 0}
    };

    int time = 0;                 // simulation clock
    int remaining_processes = NUM_PROCESSES;

    printf("=== Round-Robin Scheduler Simulation ===\n");
    printf("Quantum: %d units\n\n", QUANTUM);

    // Keep cycling through processes until all have finished (burst_time reaches 0)
    while (remaining_processes > 0) {
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processes[i].burst_time > 0) {
                // Determine how long this process runs THIS turn:
                // either a full quantum, or whatever's left if less than a quantum remains
                int run_time = (processes[i].burst_time > QUANTUM) ? QUANTUM : processes[i].burst_time;

                printf("Time %d: Process %d runs for %d units\n", time, processes[i].pid, run_time);

                time += run_time;
                processes[i].burst_time -= run_time;

                if (processes[i].burst_time == 0) {
                    // Process just finished - record its turnaround time
                    processes[i].turnaround_time = time;
                    remaining_processes--;
                    printf("         -> Process %d completed at time %d\n", processes[i].pid, time);
                }
            }
        }
    }

    // Calculate waiting time for each process: turnaround time minus its total burst time
    printf("\n=== Summary ===\n");
    printf("PID\tBurst\tTurnaround\tWaiting\n");

    float total_waiting = 0, total_turnaround = 0;

    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].total_burst_time;
        printf("%d\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].total_burst_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);

        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time:    %.2f\n", total_waiting / NUM_PROCESSES);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / NUM_PROCESSES);

    return 0;
}
