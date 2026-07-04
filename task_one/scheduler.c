/*
 * scheduler.c
 * Task 1: Process Management and Threading
 * Stage 3 - Fixing the race condition using a mutex
 *
 * Author: Pooja Pandey
 * Student ID: <your ID>
 * Date: 3 July 2026
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define INCREMENTS_PER_THREAD 100000

int shared_counter = 0;

// A mutex is a lock. Only one thread can "hold" it at a time.
// It must be initialized before use.
pthread_mutex_t counter_lock;

void *worker(void *arg) {
    int thread_id = *(int *)arg;

    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        pthread_mutex_lock(&counter_lock);   // acquire the lock - blocks if another thread holds it
        shared_counter++;                    // critical section: only one thread executes this at a time
        pthread_mutex_unlock(&counter_lock); // release the lock so another thread can proceed
    }

    printf("Thread %d: finished incrementing\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the mutex before any thread uses it.
    // NULL means default mutex attributes.
    pthread_mutex_init(&counter_lock, NULL);

    printf("Main: starting %d threads, each incrementing %d times (WITH mutex protection)\n",
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

    if (shared_counter == expected) {
        printf(">> Correct! Mutex successfully prevented the race condition.\n");
    } else {
        printf(">> Unexpected: mismatch still occurred (should not happen with correct locking).\n");
    }

    // Clean up the mutex once we're done with it - good practice, avoids resource leaks.
    pthread_mutex_destroy(&counter_lock);

    return 0;
}
