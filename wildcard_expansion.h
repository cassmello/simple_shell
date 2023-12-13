#ifndef WILDCARD_EXPANSION_H
#define WILDCARD_EXPANSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

// Function to perform wildcard expansion
char** expand_wildcards(char **tokens);

// Function to free memory allocated during wildcard expansion
void free_expanded_tokens(char **expanded_tokens);

#endif /* WILDCARD_EXPANSION_H */

