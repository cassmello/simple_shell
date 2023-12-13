#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || value == NULL)
    {
        fprintf(stderr, "Invalid arguments\n");
        return -1;
    }

    // Check if the variable already exists
    char *existing_value = _getenv(name);

    if (existing_value != NULL)
    {
        // Variable exists, check if overwrite is allowed
        if (!overwrite)
        {
            fprintf(stderr, "Variable %s already exists\n", name);
            return -1;
        }

        // Overwrite the existing value
        size_t len = strlen(name) + strlen(value) + 2; // +2 for '=' and '\0'
        char *new_entry = malloc(len);

        if (new_entry == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        snprintf(new_entry, len, "%s=%s", name, value);

        // Replace the existing entry in environ
        for (unsigned int i = 0; environ[i] != NULL; i++)
        {
            if (strncmp(environ[i], name, strlen(name)) == 0)
            {
                free(environ[i]);
                environ[i] = new_entry;
                return 0;
            }
        }

        // If we didn't find the variable in environ (should not happen)
        free(new_entry);
        fprintf(stderr, "Error updating variable %s\n", name);
        return -1;
    }
    else
    {
        // Variable does not exist, create a new entry
        size_t len = strlen(name) + strlen(value) + 2; // +2 for '=' and '\0'
        char *new_entry = malloc(len);

        if (new_entry == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        snprintf(new_entry, len, "%s=%s", name, value);

        // Count the number of existing entries in environ
        unsigned int count = 0;
        while (environ[count] != NULL)
            count++;

        // Allocate space for the new entry
        char **new_environ = realloc(environ, (count + 2) * sizeof(char *));
        if (new_environ == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Add the new entry to environ
        new_environ[count] = new_entry;
        new_environ[count + 1] = NULL;
        environ = new_environ;

        return 0;
    }
}

