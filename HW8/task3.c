#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char path[256];

    printf("Enter file path: ");
    if (scanf("%255s", path) != 1) {
        fprintf(stderr, "Failed to read path\n");
        return 1;
    }

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    char byte;
    for (off_t i = size - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            return 1;
        }
        if (read(fd, &byte, 1) != 1) {
            perror("read");
            close(fd);
            return 1;
        }
        if (write(STDOUT_FILENO, &byte, 1) != 1) {
            perror("write stdout");
            close(fd);
            return 1;
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    close(fd);
    return 0;
}
