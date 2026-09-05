#include <stdio.h>

int main() {
    int num = 2165;
	int *ptr = &num;
	
    printf("Address of num: %p\n", &num);
    printf("Address stored in ptr: %p\n", ptr);

    *ptr = 5652;
    printf("New value of num: %d\n", num);

    return 0;
}
