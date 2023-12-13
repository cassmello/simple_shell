#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Custom signal handler for SIGINT
void sigintHandler(int sig) {
    printf("\nSIGINT received. Do you really want to exit? (Y/N): ");
    char response;
    scanf(" %c", &response);

    if (response == 'Y' || response == 'y') {
        exit(EXIT_SUCCESS);
    } else {
        // Reinstall the signal handler
        signal(SIGINT, sigintHandler);
    }
}

// Function to initialize signal handlers
void initializeSignalHandlers() {
    // Register the custom signal handler for SIGINT
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }
}

