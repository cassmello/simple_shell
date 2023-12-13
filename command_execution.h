#ifndef COMMAND_EXECUTION_H
#define COMMAND_EXECUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to execute an external command
void execute_command(char **tokens);

#endif /* COMMAND_EXECUTION_H */

