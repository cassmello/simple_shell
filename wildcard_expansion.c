#include "wildcard_expansion.h"

// Function to perform wildcard expansion
char** expand_wildcards(char **tokens) {
    char **expanded_tokens = NULL;

    for (int i = 0; tokens[i] != NULL; i++) {
        // Check if the token contains wildcards
        if (strchr(tokens[i], '*') != NULL || strchr(tokens[i], '?') != NULL) {
            glob_t glob_result;

            // Perform wildcard expansion
            if (glob(tokens[i], GLOB_NOCHECK, NULL, &glob_result) == 0) {
                // Add the expanded paths to the list
                for (size_t j = 0; j < glob_result.gl_pathc; j++) {
                    expanded_tokens = realloc(expanded_tokens, (i + 2) * sizeof(char*));
                    if (expanded_tokens == NULL) {
                        perror("Memory allocation error");
                        exit(EXIT_FAILURE);
                    }

                    expanded_tokens[i] = strdup(glob_result.gl_pathv[j]);
                    if (expanded_tokens[i] == NULL) {
                        perror("Memory allocation error");
                        exit(EXIT_FAILURE);
                    }
                    expanded_tokens[i + 1] = NULL;
                }

                // Free the glob result structure
                globfree(&glob_result);
            } else {
                // If glob returns an error, keep the original token
                expanded_tokens = realloc(expanded_tokens, (i + 2) * sizeof(char*));
                if (expanded_tokens == NULL) {
                    perror("Memory allocation error");
                    exit(EXIT_FAILURE);
                }

                expanded_tokens[i] = strdup(tokens[i]);
                if (expanded_tokens[i] == NULL) {
                    perror("Memory allocation error");
                    exit(EXIT_FAILURE);
                }
                expanded_tokens[i + 1] = NULL;
            }
        } else {
            // No wildcard, keep the original token
            expanded_tokens = realloc(expanded_tokens, (i + 2) * sizeof(char*));
            if (expanded_tokens == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            expanded_tokens[i] = strdup(tokens[i]);
            if (expanded_tokens[i] == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            expanded_tokens[i + 1] = NULL;
        }
    }

    return expanded_tokens;
}

// Function to free memory allocated during wildcard expansion
void free_expanded_tokens(char **expanded_tokens) {
    if (expanded_tokens == NULL) {
        return;
    }

    for (int i = 0; expanded_tokens[i] != NULL; i++) {
        free(expanded_tokens[i]);
    }

    free(expanded_tokens);
}

