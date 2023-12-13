#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "myshell_config.txt"
#define MAX_CONFIG_LINE 256

typedef struct {
    char key[MAX_CONFIG_LINE];
    char value[MAX_CONFIG_LINE];
} ConfigEntry;

ConfigEntry* config_entries = NULL;
int config_entry_count = 0;

void read_config_file() {
    FILE* file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open config file %s\n", CONFIG_FILE);
        return;
    }

    while (!feof(file)) {
        ConfigEntry entry;
        if (fscanf(file, "%s = %s\n", entry.key, entry.value) == 2) {
            config_entry_count++;
            config_entries = (ConfigEntry*)realloc(config_entries, config_entry_count * sizeof(ConfigEntry));
            config_entries[config_entry_count - 1] = entry;
        }
    }

    fclose(file);
}

void apply_config_settings() {
    for (int i = 0; i < config_entry_count; ++i) {
        // Example: Apply config settings based on key-value pairs
        if (strcmp(config_entries[i].key, "prompt") == 0) {
            printf("Setting prompt: %s\n", config_entries[i].value);
            // Implement the logic to change the shell prompt
        }
        // Add more conditions for other config settings
    }
}

void free_config_entries() {
    free(config_entries);
}

int main() {
    read_config_file();
    apply_config_settings();

    // Continue with the main shell loop and other functionalities

    // Cleanup
    free_config_entries();

    return 0;
}

