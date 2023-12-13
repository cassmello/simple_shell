#include "io_redirection.h"

// Function to perform I/O redirection and execute a command
void execute_with_redirection(char **tokens) {
    pid_t pid, wpid;
    int status;
    int fd_in, fd_out;

    // Find input and output redirection symbols
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "<") == 0) {
            // Input redirection
            fd_in = open(tokens[i + 1], O_RDONLY);
            if (fd_in == -1) {
                perror("Input redirection error");
                return;
            }

            dup2(fd_in, STDIN_FILENO);
            close(fd_in);

            // Remove the redirection symbols and the filename from tokens
            for (int j = i; tokens[j] != NULL; j++) {
                tokens[j] = tokens[j + 2];
            }
        } else if (strcmp(tokens[i], ">") == 0) {
            // Output redirection
            fd_out = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd_out == -1) {
                perror("Output redirection error");
                return;
            }

            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);

            // Remove the redirection symbols and the filename from tokens
            for (int j = i; tokens[j] != NULL; j++) {
                tokens[j] = tokens[j + 2];
            }
        }
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
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

