#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executeScript(const char* scriptPath) {
    FILE* scriptFile = fopen(scriptPath, "r");

    if (scriptFile == NULL) {
        perror("Error opening script file");
        return;
    }

    char line[256];  // Adjust the buffer size as needed

    // Read and execute each line from the script
    while (fgets(line, sizeof(line), scriptFile) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Execute the command
        system(line);
    }

    fclose(scriptFile);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s script_path\n", argv[0]);
        return EXIT_FAILURE;
    }

    executeScript(argv[1]);

    return EXIT_SUCCESS;
}

