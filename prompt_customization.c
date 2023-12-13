#include "prompt_customization.h"

// Function to generate a custom shell prompt
char* generate_prompt() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("Failed to get hostname");
        exit(EXIT_FAILURE);
    }

    char username[256];
    if (getlogin_r(username, sizeof(username)) != 0) {
        perror("Failed to get username");
        exit(EXIT_FAILURE);
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Failed to get current directory");
        exit(EXIT_FAILURE);
    }

    // Customize the prompt format as needed
    char* prompt = malloc(strlen(username) + strlen(hostname) + strlen(cwd) + 20);  // Assuming a certain length for the prompt
    if (prompt == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    sprintf(prompt, "%s@%s:%s $ ", username, hostname, cwd);
    return prompt;
}

