#ifndef COMMAND_LINE_PARSING_H
#define COMMAND_LINE_PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

// Function to parse user input into an array of tokens
void parse_input(char *input, char **tokens);

#endif /* COMMAND_LINE_PARSING_H */

