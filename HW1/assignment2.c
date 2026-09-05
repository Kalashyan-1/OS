#include <stdio.h>

int main() {
    int arr[5] = {15105, 564556, 156306, 5406, 94506};
    int *ptr = arr;

    printf("Original array:\n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }

    printf("\n");

    for (int i = 0; i < 5; i++) {
        *(ptr + i) = *(ptr + i) + 6145;
    }

    printf("Modified array using pointer:\n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }

    printf("\nModified array using array name:\n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
