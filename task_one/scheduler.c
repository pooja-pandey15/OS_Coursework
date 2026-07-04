/*
 * scheduler.c
 * Task 1: Process Management and Threading
 * Stage 5 - Deadlock demonstration and prevention
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex_A;
pthread_mutex_t mutex_B;

// Set to 1 to run the UNSAFE version (inconsistent lock order -> can deadlock)
// Set to 0 to run the SAFE version (consistent lock order -> no deadlock)
#define UNSAFE_MODE 0

// Helper: lock a mutex with a timeout, so our demo never hangs forever.
// Returns 0 on success, non-zero if it timed out waiting (a sign of deadlock).
int lock_with_timeout(pthread_mutex_t *m, int seconds) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += seconds;
    return pthread_mutex_timedlock(m, &ts);
}

void *thread_A(void *arg) {
    printf("Thread A: locking mutex_A...\n");
    pthread_mutex_lock(&mutex_A);
    printf("Thread A: locked mutex_A. Sleeping to widen the race window...\n");
    sleep(1); // gives Thread B time to lock mutex_B, setting up the deadlock

    printf("Thread A: trying to lock mutex_B...\n");
    if (lock_with_timeout(&mutex_B, 3) == 0) {
        printf("Thread A: locked mutex_B. Working...\n");
        pthread_mutex_unlock(&mutex_B);
    } else {
        printf("Thread A: TIMED OUT waiting for mutex_B -> deadlock detected!\n");
    }

    pthread_mutex_unlock(&mutex_A);
    return NULL;
}

void *thread_B(void *arg) {
#if UNSAFE_MODE
    printf("Thread B: locking mutex_B...\n");
    pthread_mutex_lock(&mutex_B);
    printf("Thread B: locked mutex_B. Sleeping to widen the race window...\n");
    sleep(1);

    printf("Thread B: trying to lock mutex_A...\n");
    if (lock_with_timeout(&mutex_A, 3) == 0) {
        printf("Thread B: locked mutex_A. Working...\n");
        pthread_mutex_unlock(&mutex_A);
    } else {
        printf("Thread B: TIMED OUT waiting for mutex_A -> deadlock detected!\n");
    }
    pthread_mutex_unlock(&mutex_B);
#else
    // SAFE VERSION: Thread B acquires locks in the SAME order as Thread A
    // (mutex_A first, then mutex_B). This consistent ordering removes the
    // circular wait condition required for deadlock.
    printf("Thread B: locking mutex_A...\n");
    pthread_mutex_lock(&mutex_A);
    printf("Thread B: locked mutex_A. Sleeping to widen the race window...\n");
    sleep(1);

    printf("Thread B: trying to lock mutex_B...\n");
    pthread_mutex_lock(&mutex_B);
    printf("Thread B: locked mutex_B. Working...\n");
    pthread_mutex_unlock(&mutex_B);

    pthread_mutex_unlock(&mutex_A);
#endif
    return NULL;
}

int main() {
    pthread_t tA, tB;

    pthread_mutex_init(&mutex_A, NULL);
    pthread_mutex_init(&mutex_B, NULL);

#if UNSAFE_MODE
    printf("=== Running UNSAFE version (inconsistent lock order) ===\n\n");
#else
    printf("=== Running SAFE version (consistent lock order) ===\n\n");
#endif

    pthread_create(&tA, NULL, thread_A, NULL);
    pthread_create(&tB, NULL, thread_B, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    printf("\nMain: both threads finished.\n");

    pthread_mutex_destroy(&mutex_A);
    pthread_mutex_destroy(&mutex_B);

    return 0;
}
