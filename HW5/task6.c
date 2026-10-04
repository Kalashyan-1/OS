#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL)
        return malloc(new_size);

    void *new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;

    size_t copy_size = old_size < new_size ? old_size : new_size;
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    return new_ptr;
}

int main() {
    int old_count = 5, new_count = 8;

    int *arr = (int *)malloc(old_count * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        exit(1);
    }

    for (int i = 0; i < old_count; i++)
        arr[i] = (i + 1) * 10;

    printf("Original array (%d elements): ", old_count);
    for (int i = 0; i < old_count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    arr = (int *)my_realloc(arr, old_count * sizeof(int), new_count * sizeof(int));
    if (arr == NULL) {
        perror("my_realloc failed");
        exit(1);
    }

    for (int i = old_count; i < new_count; i++)
        arr[i] = (i + 1) * 10;

    printf("Resized array (%d elements): ", new_count);
    for (int i = 0; i < new_count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int shrink_count = 3;
    arr = (int *)my_realloc(arr, new_count * sizeof(int), shrink_count * sizeof(int));
    if (arr == NULL) {
        perror("my_realloc failed");
        exit(1);
    }

    printf("Shrunk array (%d elements): ", shrink_count);
    for (int i = 0; i < shrink_count; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
