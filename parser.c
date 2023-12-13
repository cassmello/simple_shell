// parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 20

// Function declarations
char** parseInput(char *input);

void freeArgs(char **args);

char** parseInput(char *input) {
    // Tokenize the input
    char **args = malloc(MAX_ARGS * sizeof(char*));
    if (!args) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_ARGS; i++) {
        args[i] = malloc(MAX_ARG_LENGTH * sizeof(char));
        if (!args[i]) {
            perror("Memory allocation error");
            freeArgs(args);
            exit(EXIT_FAILURE);
        }
    }

    int argCount = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        strcpy(args[argCount++], token);
        token = strtok(NULL, " ");

        if (argCount >= MAX_ARGS) {
            fprintf(stderr, "Too many arguments. Maximum allowed is %d.\n", MAX_ARGS);
            freeArgs(args);
            exit(EXIT_FAILURE);
        }
    }

    args[argCount] = NULL;  // Set the last argument to NULL to indicate the end

    return args;
}

void freeArgs(char **args) {
    for (int i = 0; i < MAX_ARGS; i++) {
        free(args[i]);
    }
    free(args);
}

