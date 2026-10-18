#include <stdio.h>
#include <stddef.h>

struct NoPack {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct Pack1 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct Pack2 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct Pack4 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

int main() {
    struct NoPack np;
    struct Pack1 p1;
    struct Pack2 p2;
    struct Pack4 p4;

    printf("sizeof(NoPack) = %zu bytes\n", sizeof(struct NoPack));
    printf("Offset of a: %zu\n", offsetof(struct NoPack, a));
    printf("Offset of b: %zu\n", offsetof(struct NoPack, b));
    printf("Offset of c: %zu\n", offsetof(struct NoPack, c));
    printf("Address of np.a: %p\n", &np.a);
    printf("Address of np.b: %p\n", &np.b);
    printf("Address of np.c: %p\n", &np.c);

    printf("sizeof(Pack1) = %zu bytes\n", sizeof(struct Pack1));
    printf("Offset of a: %zu\n", offsetof(struct Pack1, a));
    printf("Offset of b: %zu\n", offsetof(struct Pack1, b));
    printf("Offset of c: %zu\n", offsetof(struct Pack1, c));
    printf("Address of p1.a: %p\n", &p1.a);
    printf("Address of p1.b: %p\n", &p1.b);
    printf("Address of p1.c: %p\n", &p1.c);

    printf("sizeof(Pack2) = %zu bytes\n", sizeof(struct Pack2));
    printf("Offset of a: %zu\n", offsetof(struct Pack2, a));
    printf("Offset of b: %zu\n", offsetof(struct Pack2, b));
    printf("Offset of c: %zu\n", offsetof(struct Pack2, c));
    printf("Address of p2.a: %p\n", &p2.a);
    printf("Address of p2.b: %p\n", &p2.b);
    printf("Address of p2.c: %p\n", &p2.c);

    printf("sizeof(Pack4) = %zu bytes\n", sizeof(struct Pack4));
    printf("Offset of a: %zu\n", offsetof(struct Pack4, a));
    printf("Offset of b: %zu\n", offsetof(struct Pack4, b));
    printf("Offset of c: %zu\n", offsetof(struct Pack4, c));
    printf("Address of p4.a: %p\n", &p4.a);
    printf("Address of p4.b: %p\n", &p4.b);
    printf("Address of p4.c: %p\n", &p4.c);

    return 0;
}
