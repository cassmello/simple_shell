#include "configurability.h"

#define MAX_LINE_LENGTH 1024

// Example configuration settings
static char prompt_format[MAX_LINE_LENGTH] = "%s@%s:%s $ ";
static int history_size = 100;

// Function to load configuration settings from a file
int load_configuration(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening configuration file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse and set configuration settings based on the content of the file
        char *token = strtok(line, "=");
        if (token != NULL) {
            // Remove leading and trailing whitespaces
            char *setting_name = strtok(token, " \t\n");
            char *setting_value = strtok(NULL, " \t\n");

            if (setting_name != NULL && setting_value != NULL) {
                if (strcmp(setting_name, "PROMPT_FORMAT") == 0) {
                    strncpy(prompt_format, setting_value, sizeof(prompt_format));
                } else if (strcmp(setting_name, "HISTORY_SIZE") == 0) {
                    history_size = atoi(setting_value);
                }
            }
        }
    }

    fclose(file);
    return 1;
}

// Function to apply configuration settings
void apply_configuration() {
    // Apply configuration settings as needed
    printf("Applying configuration:\n");
    printf("Prompt Format: %s\n", prompt_format);
    printf("History Size: %d\n", history_size);
}

