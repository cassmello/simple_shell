#include "command_substitution.h"

// Function to perform command substitution
char* substitute_commands(char *input) {
    char *expanded_input = malloc(strlen(input) + 1);
    if (expanded_input == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 0, j = 0; input[i] != '\0'; i++, j++) {
        if (input[i] == '$' && input[i + 1] == '(') {
            // Found '$(', try to substitute command
            int command_start = i + 2;
            int command_end = command_start;

            // Find the end of the command substitution
            while (input[command_end] != '\0' && input[command_end] != ')') {
                command_end++;
            }

            if (input[command_end] == ')') {
                // Extract the command to substitute
                char command[command_end - command_start + 1];
                strncpy(command, &input[command_start], command_end - command_start);
                command[command_end - command_start] = '\0';

                // Execute the command and capture its output
                FILE *fp = popen(command, "r");
                if (fp == NULL) {
                    perror("Command substitution error");
                    exit(EXIT_FAILURE);
                }

                // Read the output of the command
                char command_output[1024];
                fgets(command_output, sizeof(command_output), fp);

                // Close the pipe
                pclose(fp);

                // Replace the command substitution with its output
                strcpy(&expanded_input[j], command_output);
                j += strlen(command_output) - 1;

                // Move the index past the command substitution
                i = command_end;
            } else {
                // If ')' not found, copy the characters as is
                expanded_input[j] = input[i];
            }
        } else {
            // Copy the character as is
            expanded_input[j] = input[i];
        }
    }

    expanded_input[j] = '\0';
    return expanded_input;
}

