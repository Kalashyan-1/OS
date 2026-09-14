#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        exit(10);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("Child 2: PID = %d\n", getpid());
        sleep(1);
        exit(20);
    }

    printf("Parent: waiting for Child 2 (PID = %d) using waitpid()\n", pid2);
    waitpid(pid2, &status, 0);
    if (WIFEXITED(status))
        printf("Child 2 exited with status %d\n", WEXITSTATUS(status));

    printf("Parent: waiting for any remaining child using wait()\n");
    wait(&status);
    if (WIFEXITED(status))
        printf("Child 1 exited with status %d\n", WEXITSTATUS(status));

    printf("Parent process done\n");

    return 0;
}
