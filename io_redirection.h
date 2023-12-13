#ifndef IO_REDIRECTION_H
#define IO_REDIRECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Function to perform I/O redirection and execute a command
void execute_with_redirection(char **tokens);

#endif /* IO_REDIRECTION_H */

