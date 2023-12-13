#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

char **splitString(const char *str) {
    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (!words) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    char *token = strtok((char *)str, " \t\n"); // Split by space, tab, and newline
    int count = 0;

    while (token != NULL) {
        words[count] = strdup(token);
        if (!words[count]) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        count++;

        token = strtok(NULL, " \t\n");
    }

    words[count] = NULL; // Null-terminate the array

    return words;
}

int main(void) {
    const char *command = "ls -l -a";

    char **arguments = splitString(command);

    for (int i = 0; arguments[i] != NULL; i++) {
        printf("Argument %d: %s\n", i, arguments[i]);
    }

    // Don't forget to free the allocated memory
    for (int i = 0; arguments[i] != NULL; i++) {
        free(arguments[i]);
    }
    free(arguments);

    return 0;
}

