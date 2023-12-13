#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_SIZE 100
#define MAX_INPUT_SIZE 1024

typedef struct {
    char* alias;
    char* command;
} Alias;

Alias* aliases[MAX_ALIAS_SIZE];
int alias_count = 0;

void add_alias(const char* alias, const char* command) {
    if (alias_count < MAX_ALIAS_SIZE) {
        aliases[alias_count] = (Alias*)malloc(sizeof(Alias));
        aliases[alias_count]->alias = strdup(alias);
        aliases[alias_count]->command = strdup(command);
        alias_count++;
    } else {
        fprintf(stderr, "Error: Maximum number of aliases reached.\n");
    }
}

char* expand_alias(const char* input) {
    for (int i = 0; i < alias_count; ++i) {
        if (strcmp(input, aliases[i]->alias) == 0) {
            return strdup(aliases[i]->command);
        }
    }
    return strdup(input);
}

void free_aliases() {
    for (int i = 0; i < alias_count; ++i) {
        free(aliases[i]->alias);
        free(aliases[i]->command);
        free(aliases[i]);
    }
}

int main() {
    while (1) {
        char buffer[MAX_INPUT_SIZE];
        printf("myshell> ");
        fgets(buffer, sizeof(buffer), stdin);

        // Remove newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Process command expansion
        char* expanded_command = expand_alias(buffer);
        printf("Expanded Command: %s\n", expanded_command);

        // Process other user input (execute command, etc.)

        free(expanded_command);
    }

    // Cleanup
    free_aliases();

    return 0;
}

