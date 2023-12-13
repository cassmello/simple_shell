#ifndef BACKGROUND_PROCESSES_H
#define BACKGROUND_PROCESSES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Function to perform background process execution
void execute_in_background(char **tokens);

#endif /* BACKGROUND_PROCESSES_H */

