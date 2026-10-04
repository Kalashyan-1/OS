#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int initial = 3, extra = 2, total = initial + extra;

    char **strings = (char **)malloc(initial * sizeof(char *));
    if (strings == NULL) {
        perror("malloc failed");
        exit(1);
    }

    printf("Enter %d strings: ", initial);
    for (int i = 0; i < initial; i++) {
        strings[i] = (char *)malloc(50 * sizeof(char));
        if (strings[i] == NULL) {
            perror("malloc failed");
            exit(1);
        }
        scanf("%49s", strings[i]);
    }

    strings = (char **)realloc(strings, total * sizeof(char *));
    if (strings == NULL) {
        perror("realloc failed");
        exit(1);
    }

    printf("Enter %d more strings: ", extra);
    for (int i = initial; i < total; i++) {
        strings[i] = (char *)malloc(50 * sizeof(char));
        if (strings[i] == NULL) {
            perror("malloc failed");
            exit(1);
        }
        scanf("%49s", strings[i]);
    }

    printf("All strings: ");
    for (int i = 0; i < total; i++)
        printf("%s ", strings[i]);
    printf("\n");

    for (int i = 0; i < total; i++)
        free(strings[i]);
    free(strings);

    return 0;
}
