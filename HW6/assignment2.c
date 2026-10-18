#include <stdio.h>
#include <stddef.h>

struct Struct1 {
    char a;
    int b;
    double c;
};

struct Struct2 {
    double c;
    int b;
    char a;
};

int main() {
    struct Struct1 s1;
    struct Struct2 s2;

    printf("sizeof(Struct1) = %zu bytes\n", sizeof(struct Struct1));
    printf("Address of s1:   %p\n", &s1);
    printf("Address of s1.a: %p (offset: %zu)\n", &s1.a, offsetof(struct Struct1, a));
    printf("Address of s1.b: %p (offset: %zu)\n", &s1.b, offsetof(struct Struct1, b));
    printf("Address of s1.c: %p (offset: %zu)\n", &s1.c, offsetof(struct Struct1, c));

    printf("sizeof(Struct2) = %zu bytes\n", sizeof(struct Struct2));
    printf("Address of s2:   %p\n", &s2);
    printf("Address of s2.c: %p (offset: %zu)\n", &s2.c, offsetof(struct Struct2, c));
    printf("Address of s2.b: %p (offset: %zu)\n", &s2.b, offsetof(struct Struct2, b));
    printf("Address of s2.a: %p (offset: %zu)\n", &s2.a, offsetof(struct Struct2, a));

    printf("Struct1 (char, int, double): %zu bytes\n", sizeof(struct Struct1));
    printf("Struct2 (double, int, char): %zu bytes\n", sizeof(struct Struct2));

    return 0;
}
