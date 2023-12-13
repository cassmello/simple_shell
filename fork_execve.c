#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 5; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            // Fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *args[] = {"ls", "-l", "/tmp", NULL};
            execve("/bin/ls", args, NULL);

            // If execve fails
            perror("Error");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}

