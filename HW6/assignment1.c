#include <stdio.h>

int main() {
    char c = 'A';
    short s = 10;
    int i = 100;
    double d = 3.14;

    printf("sizeof(char)   = %zu bytes\n", sizeof(char));
    printf("sizeof(short)  = %zu bytes\n", sizeof(short));
    printf("sizeof(int)    = %zu bytes\n", sizeof(int));
    printf("sizeof(double) = %zu bytes\n", sizeof(double));

    printf("Address of c (char):   %p\n", &c);
    printf("Address of s (short):  %p\n", &s);
    printf("Address of i (int):    %p\n", &i);
    printf("Address of d (double): %p\n", &d);

    printf("c addr %% 1 = %lu (aligned to 1-byte: %s)\n", (unsigned long)&c % 1, "Yes");
    printf("s addr %% 2 = %lu (aligned to 2-byte: %s)\n", (unsigned long)&s % 2, ((unsigned long)&s % 2 == 0) ? "Yes" : "No");
    printf("i addr %% 4 = %lu (aligned to 4-byte: %s)\n", (unsigned long)&i % 4, ((unsigned long)&i % 4 == 0) ? "Yes" : "No");
    printf("d addr %% 8 = %lu (aligned to 8-byte: %s)\n", (unsigned long)&d % 8, ((unsigned long)&d % 8 == 0) ? "Yes" : "No");

    return 0;
}
