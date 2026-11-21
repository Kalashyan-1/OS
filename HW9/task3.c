#include <stdio.h>
#include <pthread.h>

void *print_numbers(void *arg) {
    int id = *(int *)arg;

    for (int i = 1; i <= 5; i++)
        printf("Thread %d: %d\n", id, i);

    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, print_numbers, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
