#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
        return NULL;

    size_t total = size + alignment + sizeof(void *);
    void *raw = malloc(total);
    if (raw == NULL)
        return NULL;

    uintptr_t raw_addr = (uintptr_t)raw + sizeof(void *);
    uintptr_t aligned_addr = (raw_addr + alignment - 1) & ~(alignment - 1);

    ((void **)aligned_addr)[-1] = raw;

    return (void *)aligned_addr;
}

void aligned_free(void *ptr) {
    if (ptr == NULL)
        return;
    void *raw = ((void **)ptr)[-1];
    free(raw);
}

int main() {
    size_t alignments[] = {16, 32, 64, 128, 256};
    int count = sizeof(alignments) / sizeof(alignments[0]);

    for (int i = 0; i < count; i++) {
        size_t align = alignments[i];
        void *ptr = aligned_malloc(100, align);
        if (ptr == NULL) {
            printf("aligned_malloc failed for alignment %zu\n", align);
            continue;
        }

        printf("Alignment: %3zu | Address: %p | Aligned: %s\n",
               align, ptr, ((uintptr_t)ptr % align == 0) ? "Yes" : "No");

        memset(ptr, 0, 100);
        aligned_free(ptr);
    }

    return 0;
}
