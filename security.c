#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_command_allowed(const char* command) {
    // Example: Restricting specific commands
    const char* restricted_commands[] = {"rm", "dd", "mkfs", "fdisk"};
    int num_restricted_commands = sizeof(restricted_commands) / sizeof(restricted_commands[0]);

    for (int i = 0; i < num_restricted_commands; ++i) {
        if (strcmp(command, restricted_commands[i]) == 0) {
            fprintf(stderr, "Error: Command '%s' is restricted.\n", command);
            return 0; // Disallow the command
        }
    }

    return 1; // Allow the command
}

int main() {
    char command[100];

    // Get user input or command from other modules

    // Example: Check if the command is allowed
    if (is_command_allowed(command)) {
        // Execute the command or perform other actions
        printf("Executing: %s\n", command);
    }

    // Continue with the main shell loop and other functionalities

    return 0;
}

