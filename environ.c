#include <stdio.h>

extern char **environ;

int main(int ac, char **av, char **env)
{
    printf("Address of env: %p\n", env);
    printf("Address of environ: %p\n", environ);

    return (0);
}

