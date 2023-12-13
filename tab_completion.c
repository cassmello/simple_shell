#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 1024

char* get_input() {
    char buffer[MAX_INPUT_SIZE];
    printf("myshell> ");
    fgets(buffer, sizeof(buffer), stdin);

    // Remove newline character
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return strdup(buffer);
}

char** get_completion_suggestions(const char* partial_input) {
    // For simplicity, let's provide suggestions based on files in the current directory
    DIR* dir;
    struct dirent* ent;
    char** suggestions = NULL;
    int count = 0;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strncmp(ent->d_name, partial_input, strlen(partial_input)) == 0) {
                suggestions = realloc(suggestions, (count + 1) * sizeof(char*));
                suggestions[count++] = strdup(ent->d_name);
            }
        }
        closedir(dir);
    }

    suggestions = realloc(suggestions, (count + 1) * sizeof(char*));
    suggestions[count] = NULL;  // Null-terminate the array

    return suggestions;
}

void free_suggestions(char** suggestions) {
    if (suggestions != NULL) {
        for (int i = 0; suggestions[i] != NULL; ++i) {
            free(suggestions[i]);
        }
        free(suggestions);
    }
}

int main() {
    while (1) {
        char* input = get_input();

        // Check for tab key press
        if (input[0] == '\t') {
            char* partial_input = input + 1;  // Skip the tab character
            char** suggestions = get_completion_suggestions(partial_input);

            // Print suggestions
            for (int i = 0; suggestions[i] != NULL; ++i) {
                printf("%s\t", suggestions[i]);
            }
            printf("\n");

            free_suggestions(suggestions);
        } else {
            // Process other user input (execute command, etc.)
            printf("Processing: %s\n", input);
        }

        free(input);
    }

    return 0;
}

