#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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

    printf("Parent (PID = %d): not calling wait(). Child becomes zombie.\n", getpid());
    sleep(30);

    printf("Parent exiting (zombie will be cleaned up by init)\n");

    return 0;
}
