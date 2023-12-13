#include "error_handling.h"

// Function to handle errors and display error messages
void handle_error(const char *message) {
    fprintf(stderr, "Error: %s (%s)\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

