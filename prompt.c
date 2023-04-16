#include "main.h"

/**
 * shell_prompt - display shell prompt for hsh shell
*/

void shell_prompt()
{
    char host_name[MAX_LINE] = "";
    
    gethostname(host_name, sizeof(host_name));
    printf("%s@%s: %s$ ", getenv("LOGNAME"), host_name, getcwd(current_directory, MAX_LINE));
}