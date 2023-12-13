#include "command_line_parsing.h"
#include "io_redirection.h"
#include "builtin_commands.h"
#include "background_processes.h"
#include "signal_handling.h"
#include "environment_variables.h"
#include "error_handling.h"
#include "wildcard_expansion.h"
#include "variable_expansion.h"
#include "command_substitution.h"

int main() {
    char input[1024];
    char *tokens[100];

    // Set up signal handlers
    setup_signal_handlers();

    while (1) {
        // Display a prompt
        printf("MyShell $ ");
        
        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            handle_error("Failed to read input");
        }

        // Exit the shell if the user enters 'exit' or 'quit'
        if (strcmp(input, "exit\n") == 0 || strcmp(input, "quit\n") == 0) {
            printf("Exiting MyShell. Goodbye!\n");
            break;
        }

        // Parse the user input
        if (parse_input(input, tokens) != 0) {
            handle_error("Failed to parse input");
        }

        // Check if it's a built-in command
        if (!handle_builtin_commands(tokens)) {
            // Not a built-in command, expand environment variables, wildcards, variables, and commands, and execute
            char *expanded_input = expand_environment_variables(input);
            char *expanded_input_wildcards = expand_wildcards(expanded_input);
            char *expanded_input_variables = expand_variables(expanded_input_wildcards);
            char *final_input = substitute_commands(expanded_input_variables);

            if (parse_input(final_input, tokens) != 0) {
                handle_error("Failed to parse expanded input");
            }

            // Execute the command
            execute_in_background(tokens);

            // Free memory
            free(expanded_input);
            free(expanded_input_wildcards);
            free(expanded_input_variables);
            free(final_input);
        }
    }

    return 0;
}

