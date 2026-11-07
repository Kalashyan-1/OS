#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "numbers.txt";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for writing");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        char line[16];
        int len = snprintf(line, sizeof(line), "%d\n", i);
        if (write(fd, line, len) != len) {
            perror("write");
            close(fd);
            return 1;
        }
    }
    close(fd);

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open for rdwr");
        return 1;
    }

    off_t line_start = 0;
    int line_num = 0;
    char ch;

    while (read(fd, &ch, 1) == 1) {
        if (ch == '\n') {
            line_num++;
            if (line_num == 3) {
                line_start = lseek(fd, 0, SEEK_CUR);
                break;
            }
        }
    }

    off_t line4_end = line_start;
    while (read(fd, &ch, 1) == 1) {
        if (ch == '\n') {
            line4_end = lseek(fd, 0, SEEK_CUR);
            break;
        }
    }

    off_t file_end = lseek(fd, 0, SEEK_END);
    off_t remainder_size = file_end - line4_end;

    char *remainder = NULL;
    if (remainder_size > 0) {
        remainder = malloc(remainder_size);
        if (remainder == NULL) {
            perror("malloc");
            close(fd);
            return 1;
        }
        lseek(fd, line4_end, SEEK_SET);
        if (read(fd, remainder, remainder_size) != remainder_size) {
            perror("read remainder");
            free(remainder);
            close(fd);
            return 1;
        }
    }

    lseek(fd, line_start, SEEK_SET);
    const char *new_line = "100\n";
    int new_len = strlen(new_line);
    if (write(fd, new_line, new_len) != new_len) {
        perror("write new line");
        free(remainder);
        close(fd);
        return 1;
    }

    if (remainder_size > 0) {
        if (write(fd, remainder, remainder_size) != remainder_size) {
            perror("write remainder");
            free(remainder);
            close(fd);
            return 1;
        }
        free(remainder);
        remainder = NULL;
    }

    off_t new_end = lseek(fd, 0, SEEK_CUR);
    if (ftruncate(fd, new_end) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    printf("Final file content:\n");
    lseek(fd, 0, SEEK_SET);
    char buf[256];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0)
        write(STDOUT_FILENO, buf, n);

    close(fd);
    return 0;
}
