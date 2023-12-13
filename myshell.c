#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

// Function declarations
void executeCommand(char *command);

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Print the shell prompt
        printf("myshell> ");

        // Read user input
        fgets(command, sizeof(command), stdin);

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        // Check for exit command
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell. Goodbye!\n");
            break;
        }

        // Execute the command
        executeCommand(command);
    }

    return 0;
}

void executeCommand(char *command) {
    // Fork a new process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {command, NULL};
        execvp(command, args);

        // If execvp fails
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

