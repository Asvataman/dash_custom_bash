#include <stdlib.h>
#include <string.h>

extern void std_error_dash(void);

int get_params_count(char *str)
{
    int count = -1;
    char *token, *saveptr, *temp_str = strdup(str);

    token = strtok_r(temp_str, " ", &saveptr);
    while (token != NULL)
    {
        count++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    free(temp_str);
    return count;
}

char **get_params(char *str, int params_count)
{
    char **params = NULL, *saveptr_params, *temp_str = strdup(str);
    int i = 0;

    params = (char **)malloc((params_count + 1) * sizeof(char *));
    if (!params)
    {
        std_error_dash();
        exit(EXIT_FAILURE);
    }

    params[i] = strtok_r(temp_str, " ", &saveptr_params);

    do
    {
        params[i++] = strtok_r(NULL, " ", &saveptr_params);
    } while ((params[i - 1] != NULL));

    params[i] = NULL;
    return params;
}

int check_redirection(char *str)
{
    char *temp_str = strdup(str);

    if (*temp_str == '>')
    {
        free(temp_str);
        return -1;
    }

    char *redirect_pos = strchr(temp_str, '>');

    if (redirect_pos == NULL)
    {
        free(temp_str);
        return 0;
    }

    if (strchr(redirect_pos + 1, '>') != NULL)
    {
        free(temp_str);
        return -1;
    }

    redirect_pos++;
    char *token = strtok(redirect_pos, " ");

    if (token == NULL)
    {
        free(temp_str);
        return -1;
    }

    if (strtok(NULL, " ") != NULL)
    {
        free(temp_str);
        return -1;
    }

    free(temp_str);
    return 1;
}

char **get_args(char *command)
{
    char **params, *saveptr_params;
    int i = 0, params_count = 0;
    char *temp_command = strdup(command);
    // printf("7.%s\n",temp_command);

    params_count = get_params_count(temp_command);
    // printf("8.%d\n",params_count);
    params = (char **)malloc((params_count + 2) * sizeof(char *));
    // printf("88.%s\n",temp_command);
    params[i++] = strtok_r(temp_command, " ", &saveptr_params);
    // printf("9.%s\t %d\n",params[i-1],i-1);

    while ((params[i - 1] != NULL))
    {
        params[i++] = strtok_r(NULL, " ", &saveptr_params);
        // printf("9.%s\t %d\n",params[i-1],i-1);
    }

    params[i - 1] = NULL;
    return params;
}