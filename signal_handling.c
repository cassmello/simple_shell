#include "signal_handling.h"

// Function to handle the SIGCHLD signal (child process termination)
void sigchld_handler(int signo) {
    (void)signo;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Function to handle the SIGINT signal (interrupt)
void sigint_handler(int signo) {
    (void)signo;
    printf("\nMyShell $ ");
    fflush(stdout);
}

// Function to set up signal handlers
void setup_signal_handlers() {
    // Set up SIGCHLD handler
    struct sigaction sa_chld;
    sa_chld.sa_handler = sigchld_handler;
    sa_chld.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa_chld, NULL);

    // Set up SIGINT handler
    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
}

