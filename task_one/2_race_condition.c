#include <stdio.h>
#include <pthread.h>

int jobs_done = 0;   // shared counter, no protection yet

void *printer(void *arg) {
    for (int i = 0; i < 100000; i++) {
        jobs_done++;   // two threads doing this at once can lose updates
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, printer, NULL);
    pthread_create(&t2, NULL, printer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected jobs done: 200000\n");
    printf("Actual jobs done:   %d\n", jobs_done);

    return 0;
}
