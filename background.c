#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executeInBackground(const char* command) {
    char* token;
    char* tokens[100];  // Assuming a maximum of 100 tokens in a command
    int tokenCount = 0;

    // Tokenize the command
    token = strtok(strdup(command), " ");
    while (token != NULL) {
        tokens[tokenCount++] = token;
        token = strtok(NULL, " ");
    }

    // Check for background execution
    int background = 0;
    if (tokenCount > 0 && strcmp(tokens[tokenCount - 1], "&") == 0) {
        background = 1;
        tokens[tokenCount - 1] = NULL;  // Remove "&" from the tokens
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execvp(tokens[0], tokens);
        perror("Error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        if (!background) {
            // Wait for the child to finish if not running in the background
            waitpid(pid, NULL, 0);
        }
    } else {
        perror("Fork failed");
    }
}

// You may need additional functions for more advanced background process handling

