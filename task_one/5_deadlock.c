#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// #define SAFE 0   // change to 1 to run the fixed version

#define  SAFE 1

pthread_mutex_t paper;
pthread_mutex_t toner;

void *printerA(void *arg) {
    pthread_mutex_lock(&paper);
    printf("A got paper\n");
    sleep(1);

    pthread_mutex_lock(&toner);
    printf("A got toner\n");

    pthread_mutex_unlock(&toner);
    pthread_mutex_unlock(&paper);
    return NULL;
}

void *printerB(void *arg) {
#if SAFE
    pthread_mutex_lock(&paper);   // same order as A 
    printf("B got paper\n");
    sleep(1);

    pthread_mutex_lock(&toner);
    printf("B got toner\n");
#else
    pthread_mutex_lock(&toner);   // opposite order from A - causes deadlock
    printf("B got toner\n");
    sleep(1);

    pthread_mutex_lock(&paper);
    printf("B got paper\n");
#endif

    pthread_mutex_unlock(&toner);
    pthread_mutex_unlock(&paper);
    return NULL;
}

int main() {
    pthread_t a, b;
    pthread_mutex_init(&paper, NULL);
    pthread_mutex_init(&toner, NULL);

    pthread_create(&a, NULL, printerA, NULL);
    pthread_create(&b, NULL, printerB, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);

    printf("Both printers finished\n");
    return 0;
}
