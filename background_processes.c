#include "background_processes.h"

// Function to perform background process execution
void execute_in_background(char **tokens) {
    pid_t pid;

    // Check if the last token is "&"
    int is_background = 0;
    int i;
    for (i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "&") == 0) {
            is_background = 1;
            break;
        }
    }

    // Remove the "&" from tokens
    if (is_background) {
        free(tokens[i]);
        tokens[i] = NULL;
    }

    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(tokens[0], tokens) == -1) {
            perror("Command execution error");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Fork error");
    } else {
        // Parent process
        if (!is_background) {
            // If not a background process, wait for it to complete
            int status;
            waitpid(pid, &status, 0);
        } else {
            // If a background process, continue without waiting
            printf("Background process started with PID %d\n", pid);
        }
    }
}

