#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ; // Declare the external environment variable

void search_in_path(const char *filename) {
    char *path = getenv("PATH"); // Get the PATH environment variable
    char *token = strtok(path, ":"); // Tokenize the PATH using ":"

    while (token != NULL) {
        // Construct the full path by concatenating the directory and filename
        char full_path[256];
        snprintf(full_path, sizeof(full_path), "%s/%s", token, filename);

        // Check if the file exists
        if (access(full_path, F_OK) == 0) {
            printf("%s\n", full_path);
            return;
        }

        // Move to the next directory in PATH
        token = strtok(NULL, ":");
    }

    // File not found in PATH
    printf("%s not found in PATH\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Iterate through the provided filenames
    for (int i = 1; i < argc; i++) {
        search_in_path(argv[i]);
    }

    return 0;
}

