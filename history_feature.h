#ifndef HISTORY_FEATURE_H
#define HISTORY_FEATURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 50  // Adjust the history size as needed

// Function to add a command to the history
void add_to_history(const char *command);

// Function to display the command history
void display_history();

// Function to get a command from history by index
char* get_command_from_history(int index);

#endif /* HISTORY_FEATURE_H */

