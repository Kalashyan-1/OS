#include <stdio.h>
#include <pthread.h>

int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array_size = 10;

typedef struct {
    int start;
    int end;
    int thread_id;
} ThreadArg;

void *sum_part(void *arg) {
    ThreadArg *ta = (ThreadArg *)arg;
    int sum = 0;

    for (int i = ta->start; i < ta->end; i++)
        sum += array[i];

    printf("Thread %d: sum of elements [%d..%d] = %d\n",
           ta->thread_id, ta->start, ta->end - 1, sum);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int mid = array_size / 2;

    ThreadArg args[2] = {
        {0, mid, 1},
        {mid, array_size, 2}
    };

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, sum_part, &args[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
