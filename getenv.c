#include <stdio.h>

extern char **environ;

char *_getenv(const char *name)
{
    unsigned int i = 0;
    size_t len = 0;

    // Iterate through the environment variables
    while (environ[i] != NULL)
    {
        // Find the length of the variable name
        while (environ[i][len] != '=' && environ[i][len] != '\0')
            len++;

        // Compare the variable name with the provided name
        if (strncmp(environ[i], name, len) == 0 && name[len] == '\0')
            return environ[i] + len + 1; // Return the value part of the variable

        len = 0; // Reset length for the next iteration
        i++;
    }

    return NULL; // Variable not found
}

