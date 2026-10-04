#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        exit(1);
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    printf("Sum of the array: %d\n", sum);

    free(arr);
    return 0;
}
