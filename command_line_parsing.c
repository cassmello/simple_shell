#include "command_line_parsing.h"

// Function to parse user input into an array of tokens
void parse_input(char *input, char **tokens) {
    char *token;
    int i = 0;

    // Use strtok to split the input into tokens based on space
    token = strtok(input, " \t\n");

    // Continue splitting and storing tokens until there are none left
    while (token != NULL && i < MAX_TOKENS - 1) {
        tokens[i] = strdup(token);  // Copy the token to the tokens array
        token = strtok(NULL, " \t\n");
        i++;
    }

    tokens[i] = NULL;  // Set the last element of the array to NULL to indicate the end
}

