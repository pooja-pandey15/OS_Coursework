#include <stdio.h>
#include <pthread.h>

int jobs_done = 0;
pthread_mutex_t lock;

void *printer(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        jobs_done++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, printer, NULL);
    pthread_create(&t2, NULL, printer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected jobs done: 200000\n");
    printf("Actual jobs done:   %d\n", jobs_done);

    pthread_mutex_destroy(&lock);
    return 0;
}
