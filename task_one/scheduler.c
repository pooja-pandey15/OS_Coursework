/*
 * scheduler.c
 * Task 1: Process Management and Threading
 * Stage 2 - Demonstrating a race condition (unprotected shared counter)
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define INCREMENTS_PER_THREAD 100000  // large number so the race condition becomes visible

// Shared resource - every thread reads and writes this SAME variable.
// Deliberately NOT protected yet, so we can observe the problem.
int shared_counter = 0;

void *worker(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        shared_counter++;   // NOT atomic! This is read -> add 1 -> write, in 3 separate steps.
    }

    printf("Thread %d: finished incrementing\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Main: starting %d threads, each incrementing %d times\n",
           NUM_THREADS, INCREMENTS_PER_THREAD);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int expected = NUM_THREADS * INCREMENTS_PER_THREAD;

    printf("\nExpected final value: %d\n", expected);
    printf("Actual final value:   %d\n", shared_counter);

    if (shared_counter != expected) {
        printf(">> Race condition detected! Lost %d increments due to unsynchronized access.\n",
               expected - shared_counter);
    } else {
        printf(">> No race condition observed this run (possible but unlikely at this scale).\n");
    }

    return 0;
}
