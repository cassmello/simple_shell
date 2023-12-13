#include "history_feature.h"

static char* history[HISTORY_SIZE];
static int history_count = 0;

// Function to add a command to the history
void add_to_history(const char *command) {
    // Free the oldest command if the history is full
    if (history_count == HISTORY_SIZE) {
        free(history[0]);
        // Shift the history array to make room for the new command
        for (int i = 0; i < history_count - 1; i++) {
            history[i] = history[i + 1];
        }
        history_count--;
    }

    // Add the new command to the history
    history[history_count++] = strdup(command);
}

// Function to display the command history
void display_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

// Function to get a command from history by index
char* get_command_from_history(int index) {
    if (index > 0 && index <= history_count) {
        return history[index - 1];
    } else {
        return NULL;
    }
}

