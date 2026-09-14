#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child (PID = %d): exiting now\n", getpid());
        exit(0);
    }

    printf("Parent (PID = %d): calling wait() to prevent zombie.\n", getpid());
    int status;
    wait(&status);

    if (WIFEXITED(status))
        printf("Child exited with status %d. No zombie created.\n", WEXITSTATUS(status));

    sleep(10);

    printf("Parent exiting\n");

    return 0;
}
