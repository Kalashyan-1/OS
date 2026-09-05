#include <stdio.h>

void swap(int *a, int *b) {
    *a ^= *b;
	*b ^= *a;
    *a ^= *b;
}

int main() {
    int x = 1;
    int y = 2;

    printf("Before swap:\n");
    printf("x = %d\n", x);
    printf("y = %d\n", y);

    swap(&x, &y);

    printf("\nAfter swap:\n");
    printf("x = %d\n", x);
    printf("y = %d\n", y);

    return 0;
}
