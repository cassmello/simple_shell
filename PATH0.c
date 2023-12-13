#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void print_path_directories(void)
{
    char *path = _getenv("PATH");

    // Tokenize the PATH using ":"
    char *token = strtok(path, ":");

    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }
}

