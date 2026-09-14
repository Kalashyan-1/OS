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
        execl("/bin/ls", "ls", NULL);
        perror("execl failed");
        exit(1);
    }

    wait(NULL);
    printf("Parent process done\n");

    return 0;
}
