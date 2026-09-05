#include <stdio.h>

int main() {
    int num = 100;
    int *ptr = &num;
    int **doublePtr = &ptr;

    printf("Value using pointer: %d\n", *ptr);
    printf("Value using double pointer: %d\n", **doublePtr);

    return 0;
}
