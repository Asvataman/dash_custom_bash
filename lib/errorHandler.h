#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void std_error_dash(void)
{
    int e_flag = 0;
    char error_message[30] = "An error has occurred\n";
    e_flag = write(STDERR_FILENO, error_message, strlen(error_message));

    if (e_flag == -1)
    {
        printf("ERROR");
        std_error_dash();
        return;
    }
    else
        return;
}