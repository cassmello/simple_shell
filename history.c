#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 100

char* history[HISTORY_SIZE];
int historyIndex = 0;

// Function to add a command to the history
void addToHistory(const char* command) {
    // Duplicate the command and store it in history
    history[historyIndex] = strdup(command);

    // Increment the history index and wrap around if necessary
    historyIndex = (historyIndex + 1) % HISTORY_SIZE;
}

// Function to display command history
void displayHistory() {
    printf("Command History:\n");
    int i;
    int index = historyIndex;

    // Display the last HISTORY_SIZE commands
    for (i = 0; i < HISTORY_SIZE; ++i) {
        if (history[index] != NULL) {
            printf("%d: %s\n", i + 1, history[index]);
        }

        index = (index + 1) % HISTORY_SIZE;
    }
}

// Function to get a command from history by index
const char* getFromHistory(int index) {
    if (index < 1 || index > HISTORY_SIZE || history[historyIndex - index] == NULL) {
        return NULL;
    }

    return history[historyIndex - index];
}

