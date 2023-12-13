#include "interactive_editing.h"

// Function to read a line interactively with editing support
char* read_line() {
    char *input = readline("MyShell $ ");
    if (input != NULL && *input != '\0') {
        add_history(input);
        return input;
    }
    return NULL;
}

