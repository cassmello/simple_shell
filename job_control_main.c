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
#include "quoting_escaping.h"
#include "history_feature.h"
#include "job_control.h"

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

        // Add the command to the history
        add_to_history(input);

        // Parse the user input
        if (parse_input(input, tokens) != 0) {
            handle_error("Failed to parse input");
        }

        // Check if it's a built-in command
        if (!handle_builtin_commands(tokens)) {
            // Not a built-in command, expand environment variables, wildcards, variables, commands, quote/escape, and execute
            char *expanded_input = expand_environment_variables(input);
            char *expanded_input_wildcards = expand_wildcards(expanded_input);
            char *expanded_input_variables = expand_variables(expanded_input_wildcards);
            char *expanded_input_commands = substitute_commands(expanded_input_variables);
            char *final_input = quote_and_escape(expanded_input_commands);

            if (parse_input(final_input, tokens) != 0) {
                handle_error("Failed to parse expanded input");
            }

            // Execute the command in the background and add it to the job list
            pid_t pid = execute_in_background(tokens);
            add_job(pid, input);

            // Free memory
            free(expanded_input);
            free(expanded_input_wildcards);
            free(expanded_input_variables);
            free(expanded_input_commands);
            free(final_input);
        }

        // Update the status of background jobs
        update_job_status();
    }

    // Free history memory before exiting
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }

    return 0;
}

