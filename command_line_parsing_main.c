#include "command_line_parsing.h"

int main() {
    char input[MAX_INPUT_SIZE];
    char *tokens[MAX_TOKENS];

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

        // Display parsed tokens (for demonstration purposes)
        printf("Tokens: ");
        for (int i = 0; tokens[i] != NULL; i++) {
            printf("%s ", tokens[i]);
            free(tokens[i]);  // Free memory allocated for each token
        }
        printf("\n");
    }

    return 0;
}

