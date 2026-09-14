#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2, pid3;

    printf("Initial process: PID = %d\n", getpid());

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    pid3 = fork();
    if (pid3 < 0) {
        perror("fork 3 failed");
        exit(1);
    }

    printf("PID = %d, Parent PID = %d\n", getpid(), getppid());

    while (wait(NULL) > 0);

    return 0;
}
