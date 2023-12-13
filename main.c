#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    while (1) {
        char command[100];

        // Print the shell prompt
        printf("myshell> ");

        // Read user input
        fgets(command, sizeof(command), stdin);

        // Remove newline character
        command[strlen(command) - 1] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execlp(command, command, NULL);

            // If execlp fails
            perror("Error");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            // Fork failed
            perror("Fork failed");
        }
    }

    return 0;
}

