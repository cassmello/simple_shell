// builtins.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void executeBuiltIn(char **args) {
    if (args[0] == NULL) {
        // No command provided
        return;
    }

    if (strcmp(args[0], "cd") == 0) {
        // Change directory
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
    } else if (strcmp(args[0], "exit") == 0) {
        // Exit the shell
        exit(EXIT_SUCCESS);
    } else {
        // Add more built-in commands as needed
        // Example: implement 'help', 'echo', etc.
        fprintf(stderr, "Command not found: %s\n", args[0]);
    }
}

