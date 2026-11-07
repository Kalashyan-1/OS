#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "log.txt";

    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Enter a log message: ");
    fflush(stdout);

    char input[256];
    ssize_t n = read(STDIN_FILENO, input, sizeof(input) - 1);
    if (n <= 0) {
        fprintf(stderr, "Failed to read input\n");
        close(fd);
        return 1;
    }
    input[n] = '\0';

    if (n > 0 && input[n - 1] == '\n')
        input[n - 1] = '\0';

    char line[512];
    int len = snprintf(line, sizeof(line), "PID=%d: %s\n", getpid(), input);

    if (write(fd, line, len) != len) {
        perror("write");
        close(fd);
        return 1;
    }

    /*
     * O_APPEND causes every write to atomically seek to EOF before writing.
     * So after a write, the file offset is at the end of the newly written data.
     * SEEK_CUR returns this position, which grows with each append because the
     * kernel moves the offset to EOF + bytes_written on every write call.
     */
    off_t pos = lseek(fd, 0, SEEK_CUR);
    printf("File offset after write: %ld\n", (long)pos);

    close(fd);
    return 0;
}
