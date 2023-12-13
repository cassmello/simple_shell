#include <stdio.h>

extern char **environ;

int main(void)
{
    unsigned int i = 0;

    // Iterate through the environment variables using the global variable environ
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return (0);
}

