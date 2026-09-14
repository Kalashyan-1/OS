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
        printf("Child 1 (PID = %d): exiting with code 0 (success)\n", getpid());
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork 2 failed");
        exit(1);
    }

    if (pid2 == 0) {
        printf("Child 2 (PID = %d): exiting with code 42 (error)\n", getpid());
        exit(42);
    }

    waitpid(pid1, &status, 0);
    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        printf("Child 1 exited with status %d %s\n", code,
               code == 0 ? "normal exit" : "exited with error");
    }

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        printf("Child 2 exited with status %d %s\n", code,
               code == 0 ? "normal exit" : "exited with error");
    }

    printf("Parent process done\n");

    return 0;
}
