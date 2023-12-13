#include "variable_expansion.h"

// Function to perform variable expansion
char* expand_variables(char *input) {
    char *expanded_input = malloc(strlen(input) + 1);
    if (expanded_input == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 0, j = 0; input[i] != '\0'; i++, j++) {
        if (input[i] == '$' && input[i + 1] != '\0') {
            // Found '$', try to expand variable
            char variable_name[256];
            int k;
            for (k = 0; input[i + 1] != '\0' && input[i + 1] != ' ' && input[i + 1] != '\t' && input[i + 1] != '\n'; i++, k++) {
                variable_name[k] = input[i + 1];
            }
            variable_name[k] = '\0';

            char *variable_value = getenv(variable_name);
            if (variable_value != NULL) {
                // Replace the variable with its value
                strcpy(&expanded_input[j], variable_value);
                j += strlen(variable_value) - 1;
            } else {
                // Variable not found, copy as is
                expanded_input[j] = '$';
            }
        } else {
            // Copy the character as is
            expanded_input[j] = input[i];
        }
    }

    expanded_input[j] = '\0';
    return expanded_input;
}

