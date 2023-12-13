#ifndef CONFIGURABILITY_H
#define CONFIGURABILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to load configuration settings from a file
int load_configuration(const char *filename);

// Function to apply configuration settings
void apply_configuration();

#endif /* CONFIGURABILITY_H */

