#include "simple_shell.h"

void display_prompt() {
    printf("#cisfun$ ");
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        // Read user input
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execlp(input, input, (char *)NULL) == -1) {
                // If execlp fails, print an error message
                perror("simple_shell");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                // If the child process terminated normally, print the exit status
                printf("Exit status: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                // If the child process was terminated by a signal, print the signal number
                printf("Terminated by signal: %d\n", WTERMSIG(status));
            }
        }
    }

    printf("Exiting simple_shell\n");

    return 0;
}

