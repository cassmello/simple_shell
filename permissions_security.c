#include "permissions_security.h"

// Function to check permissions before executing a command
int check_permissions(const char *command) {
    if (strstr(command, "rm") != NULL || strstr(command, "format") != NULL) {
        // Check if the command contains "rm" or "format"
        uid_t uid = getuid();
        if (uid == 0) {
            // Root user can execute any command
            return 1;
        } else {
            // Non-root users are restricted from potentially harmful commands
            fprintf(stderr, "Permission denied: You do not have permission to execute this command.\n");
            return 0;
        }
    }

    // Allow execution of other commands
    return 1;
}

