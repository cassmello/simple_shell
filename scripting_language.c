#include "scripting_language.h"
#include "command_line_parsing.h"

#define MAX_LINE_LENGTH 1024

// Function to execute a script file
void execute_script(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening script file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char *tokens[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Parse the line into tokens
        if (parse_input(line, tokens) != 0) {
            handle_error("Failed to parse script line");
            continue;
        }

        // Execute the command
        execute_in_background(tokens);
    }

    fclose(file);
}

