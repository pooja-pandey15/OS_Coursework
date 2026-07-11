#include <stdio.h>
#include <pthread.h>

// each printer just says hello and prints its number
void *printer(void *arg) {
    int id = *(int *)arg;
    printf("Printer %d is starting\n", id);
    printf("Printer %d is done\n", id);
    return NULL;
}

int main() {
    pthread_t t[3];
    int ids[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++) {
        pthread_create(&t[i], NULL, printer, &ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(t[i], NULL);
    }

    printf("All printers finished\n");
    return 0;
}
