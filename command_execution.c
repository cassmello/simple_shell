#include "command_execution.h"

// Function to execute an external command
void execute_command(char **tokens) {
    pid_t pid, wpid;
    int status;

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

