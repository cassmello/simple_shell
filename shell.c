#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Print the shell prompt
        printf("#cisfun$ ");

        // Read user input
        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Handle EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        command[strlen(command) - 1] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            // Fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(command, command, NULL);

            // If execlp fails
            perror("Error");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}

