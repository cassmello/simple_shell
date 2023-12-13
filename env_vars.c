#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printEnvironment() {
    extern char** environ;
    for (char** env = environ; *env != NULL; ++env) {
        printf("%s\n", *env);
    }
}

char* getEnvironmentVariable(const char* name) {
    return getenv(name);
}

int setEnvironmentVariable(const char* name, const char* value, int overwrite) {
    return setenv(name, value, overwrite);
}

int unsetEnvironmentVariable(const char* name) {
    return unsetenv(name);
}

int main() {
    // Print the current environment
    printf("Current environment:\n");
    printEnvironment();

    // Get the value of a specific environment variable
    const char* varName = "MY_VARIABLE";
    printf("\nValue of %s: %s\n", varName, getEnvironmentVariable(varName));

    // Set a new environment variable
    const char* newVarName = "NEW_VARIABLE";
    const char* newValue = "new_value";
    setEnvironmentVariable(newVarName, newValue, 1);
    printf("\nUpdated environment:\n");
    printEnvironment();

    // Unset the environment variable
    unsetEnvironmentVariable(newVarName);
    printf("\nEnvironment after unsetting %s:\n", newVarName);
    printEnvironment();

    return 0;
}

