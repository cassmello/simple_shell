#include "command_line_parsing.h"
#include "command_execution.h"
#include "builtin_commands.h"

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

        // Check if it's a built-in command
        if (!handle_builtin_commands(tokens)) {
            // Not a built-in command, execute it
            execute_command(tokens);
        }
    }

    return 0;
}

