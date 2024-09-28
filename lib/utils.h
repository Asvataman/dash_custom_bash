#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
extern void std_error_dash(void);

char *get_input_from_user()
{
    char *line = NULL;
    size_t buffer_size = 0;
    int len = -1;

    printf("dash> ");
    len = getline(&line, &buffer_size, stdin);

    if (len == -1)
    {
        std_error_dash();
        exit(EXIT_FAILURE);
    }
    else
    {
        if (len > 0 && (line[len - 1] == '\n'))
        {
            line[len - 1] = '\0';
        }
    }

    return line;
}

char *get_input_from_file(FILE *file)
{
    char *line = NULL;
    size_t buffer_size = 0;

    if (getline(&line, &buffer_size, file) == -1)
    {
        std_error_dash();
        exit(EXIT_FAILURE);
    }

    return line;
}

char *clean_whitespace(char *str)
{
    int i = 0, j = 0;
    int len = strlen(str);

    while (isspace(str[i]))
    {
        i++;
    }

    while (i < len)
    {
        if (!isspace(str[i]) || (j > 0 && !isspace(str[j - 1])))
        {
            str[j++] = (isspace(str[i]) ? ' ' : str[i]);
        }
        i++;
    }

    if (j > 0 && isspace(str[j - 1]))
    {
        j--;
    }

    str[j] = '\0';
    return str;
}