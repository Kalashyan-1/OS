#include <stdio.h>
#include <stdlib.h>

void cleanup_first() {
    printf("Cleanup function 1: Closing files...\n");
}

void cleanup_second() {
    printf("Cleanup function 2: Releasing resources...\n");
}

int main() {
    atexit(cleanup_first);
    atexit(cleanup_second);

    printf("Program is running...\n");
    printf("Doing some work...\n");

    printf("Calling exit() now.\n");
    exit(0);
}
