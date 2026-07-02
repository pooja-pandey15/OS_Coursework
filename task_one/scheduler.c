/*
 * scheduler.c
 * Task 1: Process Management and Threading
 * Stage 1 - Basic thread creation
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>   // for sleep()

#define NUM_THREADS 3

// This function runs inside each thread.
// pthread requires this exact signature: void* function(void* arg)
void *worker(void *arg) {
    int thread_id = *(int *)arg;  // recover this thread's ID from the pointer we passed in

    printf("Thread %d: started\n", thread_id);
    sleep(1); // simulate the thread doing some work
    printf("Thread %d: finished\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];   // holds a handle to each thread we create
    int thread_ids[NUM_THREADS];      // stores each thread's ID separately (important!)

    printf("Main: creating %d threads\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;

        // pthread_create(handle, attributes, function to run, argument to pass)
        int result = pthread_create(&threads[i], NULL, worker, &thread_ids[i]);

        if (result != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for every thread to finish before main() exits.
    // Without this, main() could end while threads are still running.
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: all threads finished\n");
    return 0;
}
