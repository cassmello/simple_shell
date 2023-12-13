#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("$ ");
        ssize_t read_size = getline(&line, &len, stdin);

        if (read_size == -1) {
            perror("getline");
            break;
        }

        if (read_size > 1) {
            // Print the entered command
            printf("You entered: %s", line);
        }
    }

    free(line);
    return 0;
}

