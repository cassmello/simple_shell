#include "command_line_parsing.h"
#include "io_redirection.h"
#include "builtin_commands.h"
#include "background_processes.h"
#include "signal_handling.h"

int main() {
    char input[1024];
    char *tokens[100];

    // Set up signal handlers
    setup_signal_handlers();

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
            // Not a built-in command, execute it with I/O redirection and background option
            execute_in_background(tokens);
        }
    }

    return 0;
}

