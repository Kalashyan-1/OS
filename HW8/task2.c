#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "data.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for writing");
        return 1;
    }
    if (write(fd, text, 26) != 26) {
        perror("write");
        close(fd);
        return 1;
    }
    close(fd);

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open for rdwr");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    printf("Current file size: %ld bytes\n", (long)size);

    if (ftruncate(fd, 10) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    off_t new_size = lseek(fd, 0, SEEK_END);
    printf("Size after truncation: %ld bytes\n", (long)new_size);

    lseek(fd, 0, SEEK_SET);
    char buf[64];
    ssize_t n = read(fd, buf, sizeof(buf));
    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    buf[n] = '\0';
    printf("Content after truncation: %s\n", buf);

    close(fd);
    return 0;
}
