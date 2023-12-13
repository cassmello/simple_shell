#include "builtin_commands.h"

// Function to handle built-in commands
int handle_builtin_commands(char **tokens) {
    if (tokens[0] == NULL) {
        // No command provided
        return 1;
    }

    if (strcmp(tokens[0], "cd") == 0) {
        // Change directory
        if (tokens[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(tokens[1]) != 0) {
                perror("cd");
            }
        }
        return 1;
    } else if (strcmp(tokens[0], "exit") == 0 || strcmp(tokens[0], "quit") == 0) {
        // Exit the shell
        printf("Exiting MyShell. Goodbye!\n");

