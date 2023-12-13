#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

typedef struct PathNode
{
    char *directory;
    struct PathNode *next;
} PathNode;

PathNode *build_path_list(void)
{
    PathNode *head = NULL;
    PathNode *current = NULL;

    char *path = _getenv("PATH");

    // Tokenize the PATH using ":"
    char *token = strtok(path, ":");

    while (token != NULL)
    {
        // Create a new node for each directory
        PathNode *node = malloc(sizeof(PathNode));
        if (node == NULL)
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        node->directory = strdup(token);
        node->next = NULL;

        // Add the node to the linked list
        if (head == NULL)
        {
            head = node;
            current = node;
        }
        else
        {
            current->next = node;
            current = node;
        }

        token = strtok(NULL, ":");
    }

    return head;
}

