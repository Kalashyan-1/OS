#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        execl("/bin/ls", "ls", NULL);
        perror("execl failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        execl("/bin/date", "date", NULL);
        perror("execl failed");
        exit(1);
    }

    while (wait(NULL) > 0);
    printf("Parent process done\n");

    return 0;
}
