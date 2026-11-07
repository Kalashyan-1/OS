#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char src_path[256], dst_path[256];

    printf("Enter source file path: ");
    if (scanf("%255s", src_path) != 1) {
        fprintf(stderr, "Failed to read source path\n");
        return 1;
    }
    printf("Enter destination file path: ");
    if (scanf("%255s", dst_path) != 1) {
        fprintf(stderr, "Failed to read destination path\n");
        return 1;
    }

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        return 1;
    }

    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    char buf[4096];
    ssize_t bytes_read;
    long total_bytes = 0;

    while ((bytes_read = read(src_fd, buf, sizeof(buf))) > 0) {
        ssize_t bytes_written = 0;
        while (bytes_written < bytes_read) {
            ssize_t w = write(dst_fd, buf + bytes_written, bytes_read - bytes_written);
            if (w == -1) {
                perror("write");
                close(src_fd);
                close(dst_fd);
                return 1;
            }
            bytes_written += w;
        }
        total_bytes += bytes_read;
    }

    if (bytes_read == -1) {
        perror("read");
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    printf("Total bytes copied: %ld\n", total_bytes);

    close(src_fd);
    close(dst_fd);
    return 0;
}
