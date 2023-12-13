#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to execute a command with input/output redirection
void executeRedirection(const char* command) {
    char* token;
    char* tokens[100];  // Assuming a maximum of 100 tokens in a command
    int tokenCount = 0;

    // Tokenize the command
    token = strtok(strdup(command), " ");
    while (token != NULL) {
        tokens[tokenCount++] = token;
        token = strtok(NULL, " ");
    }

    // Check for input/output redirection
    int redirectInput = 0, redirectOutput = 0;
    char* inputFile = NULL, *outputFile = NULL;

    for (int i = 0; i < tokenCount; ++i) {
        if (strcmp(tokens[i], "<") == 0) {
            redirectInput = 1;
            inputFile = tokens[i + 1];
            tokens[i] = NULL;
        } else if (strcmp(tokens[i], ">") == 0) {
            redirectOutput = 1;
            outputFile = tokens[i + 1];
            tokens[i] = NULL;
        } else if (strcmp(tokens[i], ">>") == 0) {
            redirectOutput = 2;  // Append
            outputFile = tokens[i + 1];
            tokens[i] = NULL;
        }
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (redirectInput) {
            int fd = open(inputFile, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (redirectOutput) {
            int fd;
            if (redirectOutput == 1) {
                fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            } else {
                fd = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(tokens[0], tokens);
        perror("Error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}

// Function to execute commands with pipes
void executePipes(const char* command) {
    // Implement pipe handling here
    // You may need to modify the code to support multiple pipes and handle command chaining
}

// You may need additional functions for more advanced redirection and pipes handling


