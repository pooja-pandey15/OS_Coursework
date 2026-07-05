/*
 * scheduler.c
 * Task 1: Process Management and Threading - Final Combined Version
 *
 * This program is split into two parts:
 *
 * PART 1: A round-robin task scheduler simulation. A shared task queue is
 *         processed by multiple worker threads, taking turns in a fixed
 *         rotation (round-robin), one task per turn. Access to the shared
 *         queue and shared counters is protected by a mutex, preventing the
 *         race conditions that would otherwise occur (see project git history,
 *         stage 2, for a demonstration of what happens without this).
 *
 * PART 2: A focused deadlock demonstration. Two threads each require two
 *         mutexes. Locks are acquired in a consistent order across all
 *         threads, which prevents the circular-wait condition required for
 *         deadlock (see project git history, stage 5, for what happens when
 *         lock order is inconsistent).
 *

 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* =====================================================================
 * PART 1: Round-robin task scheduler with mutex-protected shared queue
 * ===================================================================== */

#define NUM_WORKER_THREADS 3
#define NUM_TASKS 9
#define QUANTUM 1   // each thread does 1 task per turn before yielding

// A simple shared task queue. Tasks are represented just as numbers 0..NUM_TASKS-1
// standing in for "units of work". next_task tracks which task is next to be picked up.
int next_task = 0;
int tasks_completed = 0;

// Protects next_task and tasks_completed from simultaneous access by multiple threads.
pthread_mutex_t queue_lock;

// Tracks whose turn it is, to enforce round-robin ordering between threads.
int current_turn = 0;
pthread_cond_t turn_cond; // lets a thread sleep until it's specifically its turn

typedef struct {
    int thread_index; // 0, 1, 2, ... - used to check/enforce round-robin turn order
} WorkerArgs;

void *round_robin_worker(void *arg) {
    WorkerArgs *args = (WorkerArgs *)arg;
    int my_index = args->thread_index;

    while (1) {
        pthread_mutex_lock(&queue_lock);

        // Wait until it is this thread's turn (round-robin enforcement)
        while (current_turn != my_index && next_task < NUM_TASKS) {
            pthread_cond_wait(&turn_cond, &queue_lock);
        }

        if (next_task >= NUM_TASKS) {
            // No tasks left - wake up any other waiting threads so they can also exit
            pthread_cond_broadcast(&turn_cond);
            pthread_mutex_unlock(&queue_lock);
            break;
        }

        // Critical section: claim the next task and advance shared state.
        int my_task = next_task;
        next_task++;

        printf("Thread %d: took task %d (turn quantum = %d)\n", my_index, my_task, QUANTUM);

        // Pass the turn to the next thread in rotation (round-robin)
        current_turn = (current_turn + 1) % NUM_WORKER_THREADS;
        pthread_cond_broadcast(&turn_cond); // wake up whichever thread's turn it now is

        pthread_mutex_unlock(&queue_lock);

        // Simulate doing the work for this task (outside the lock, so other
        // threads are not blocked while this thread "works").
        usleep(200000); // 0.2 seconds per task

        pthread_mutex_lock(&queue_lock);
        tasks_completed++;
        printf("Thread %d: finished task %d (%d/%d tasks done)\n",
               my_index, my_task, tasks_completed, NUM_TASKS);
        pthread_mutex_unlock(&queue_lock);
    }

    printf("Thread %d: no tasks left, exiting.\n", my_index);
    return NULL;
}

void run_round_robin_simulation() {
    pthread_t threads[NUM_WORKER_THREADS];
    WorkerArgs args[NUM_WORKER_THREADS];

    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&turn_cond, NULL);

    printf("=== PART 1: Round-Robin Task Scheduler (%d threads, %d tasks) ===\n\n",
           NUM_WORKER_THREADS, NUM_TASKS);

    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        args[i].thread_index = i;
        pthread_create(&threads[i], NULL, round_robin_worker, &args[i]);
    }

    for (int i = 0; i < NUM_WORKER_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll tasks completed: %d/%d\n", tasks_completed, NUM_TASKS);

    pthread_mutex_destroy(&queue_lock);
    pthread_cond_destroy(&turn_cond);
}

/* =====================================================================
 * PART 2: Deadlock prevention demonstration (consistent lock ordering)
 * ===================================================================== */

pthread_mutex_t mutex_X;
pthread_mutex_t mutex_Y;

void *deadlock_safe_thread_1(void *arg) {
    printf("Deadlock-demo Thread 1: locking mutex_X...\n");
    pthread_mutex_lock(&mutex_X);
    printf("Deadlock-demo Thread 1: locked mutex_X. Working...\n");
    usleep(300000);

    printf("Deadlock-demo Thread 1: locking mutex_Y...\n");
    pthread_mutex_lock(&mutex_Y);
    printf("Deadlock-demo Thread 1: locked mutex_Y. Working...\n");

    pthread_mutex_unlock(&mutex_Y);
    pthread_mutex_unlock(&mutex_X);
    return NULL;
}

void *deadlock_safe_thread_2(void *arg) {
    // Same order as thread_1: mutex_X first, then mutex_Y.
    // This consistent ordering is what prevents circular wait / deadlock.
    printf("Deadlock-demo Thread 2: locking mutex_X...\n");
    pthread_mutex_lock(&mutex_X);
    printf("Deadlock-demo Thread 2: locked mutex_X. Working...\n");
    usleep(300000);

    printf("Deadlock-demo Thread 2: locking mutex_Y...\n");
    pthread_mutex_lock(&mutex_Y);
    printf("Deadlock-demo Thread 2: locked mutex_Y. Working...\n");

    pthread_mutex_unlock(&mutex_Y);
    pthread_mutex_unlock(&mutex_X);
    return NULL;
}

void run_deadlock_prevention_demo() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex_X, NULL);
    pthread_mutex_init(&mutex_Y, NULL);

    printf("\n=== PART 2: Deadlock Prevention Demo (consistent lock ordering) ===\n\n");

    pthread_create(&t1, NULL, deadlock_safe_thread_1, NULL);
    pthread_create(&t2, NULL, deadlock_safe_thread_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nBoth deadlock-demo threads completed successfully - no deadlock occurred,\n");
    printf("because both threads always acquire mutex_X before mutex_Y.\n");

    pthread_mutex_destroy(&mutex_X);
    pthread_mutex_destroy(&mutex_Y);
}

/* ===================================================================== */

int main() {
    run_round_robin_simulation();
    run_deadlock_prevention_demo();
    return 0;
}

