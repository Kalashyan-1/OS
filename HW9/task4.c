#include <stdio.h>
#include <pthread.h>

void *calc_square(void *arg) {
    int num = *(int *)arg;
    printf("Square of %d is %d\n", num, num * num);
    return NULL;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int count = 5;
    pthread_t threads[5];

    for (int i = 0; i < count; i++) {
        if (pthread_create(&threads[i], NULL, calc_square, &numbers[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < count; i++)
        pthread_join(threads[i], NULL);

    printf("All threads completed\n");
    return 0;
}
