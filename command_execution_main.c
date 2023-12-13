#include "command_execution.h"

int main() {
    char input[1024];
    char *tokens[100];

    while (1) {
        // Display a prompt
        printf("MyShell $ ");
        
        // Read user input
        fgets(input, sizeof(input), stdin);

        // Exit the shell if the user enters 'exit' or 'quit'
        if (strcmp(input, "exit\n") == 0 || strcmp(input, "quit\n") == 0) {
            printf("Exiting MyShell. Goodbye!\n");
            break;
        }

        // Parse the user input
        parse_input(input, tokens);

        // Execute the command
        execute_command(tokens);
    }

    return 0;
}

