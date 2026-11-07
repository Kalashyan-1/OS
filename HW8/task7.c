#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char path1[256], path2[256];

    printf("Enter first file path: ");
    if (scanf("%255s", path1) != 1) {
        fprintf(stderr, "Failed to read first path\n");
        return 1;
    }
    printf("Enter second file path: ");
    if (scanf("%255s", path2) != 1) {
        fprintf(stderr, "Failed to read second path\n");
        return 1;
    }

    int fd1 = open(path1, O_RDONLY);
    if (fd1 == -1) {
        perror("open file 1");
        return 1;
    }

    int fd2 = open(path2, O_RDONLY);
    if (fd2 == -1) {
        perror("open file 2");
        close(fd1);
        return 1;
    }

    char buf1[4096], buf2[4096];
    ssize_t n1, n2;
    long offset = 0;

    while (1) {
        n1 = read(fd1, buf1, sizeof(buf1));
        n2 = read(fd2, buf2, sizeof(buf2));

        if (n1 == -1) { perror("read file 1"); close(fd1); close(fd2); return 1; }
        if (n2 == -1) { perror("read file 2"); close(fd1); close(fd2); return 1; }

        ssize_t min = (n1 < n2) ? n1 : n2;

        for (ssize_t i = 0; i < min; i++) {
            if (buf1[i] != buf2[i]) {
                printf("Files differ at byte %ld\n", offset + i);
                close(fd1);
                close(fd2);
                return 1;
            }
        }

        offset += min;

        if (n1 != n2) {
            printf("Files differ at byte %ld\n", offset);
            close(fd1);
            close(fd2);
            return 1;
        }

        if (n1 == 0)
            break;
    }

    printf("Files are identical\n");

    close(fd1);
    close(fd2);
    return 0;
}
