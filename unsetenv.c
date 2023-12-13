#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _unsetenv(const char *name)
{
    if (name == NULL)
    {
        fprintf(stderr, "Invalid argument\n");
        return -1;
    }

    // Find the variable in environ
    for (unsigned int i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, strlen(name)) == 0)
        {
            // Variable found, remove it
            free(environ[i]);

            // Shift the remaining entries in environ
            for (unsigned int j = i; environ[j] != NULL; j++)
                environ[j] = environ[j + 1];

            return 0;
        }
    }

    // Variable not found
    fprintf(stderr, "Variable %s not found\n", name);
    return -1;
}

