#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "sparse.bin";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for writing");
        return 1;
    }

    if (write(fd, "START", 5) != 5) {
        perror("write START");
        close(fd);
        return 1;
    }

    if (lseek(fd, 1024 * 1024, SEEK_CUR) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    if (write(fd, "END", 3) != 3) {
        perror("write END");
        close(fd);
        return 1;
    }

    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open for reading");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    printf("Apparent file size: %ld bytes\n", (long)size);

    close(fd);

    /*
     * The apparent size is large (1,048,581 bytes) but disk usage (du) is
     * much smaller because the 1 MiB gap between "START" and "END" is a "hole"
     * in the file. The filesystem does not allocate disk blocks for holes — they
     * are just recorded as ranges of zeros in the file's metadata. Reading from
     * the hole returns zero bytes without using any disk space. This is called
     * a sparse file.
     */

    return 0;
}
