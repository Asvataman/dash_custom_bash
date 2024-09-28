#include "lib/commadHandler.h"

int main(int argc, char *argv[])
{
    const char *path_default = "/bin:";
    char *path;
    path = (char *)malloc(strlen(path_default) * sizeof(char) + 1);

    strcpy(path, path_default);
    FILE *stream = NULL;

    if (argc == 2)
    {
        stream = fopen(argv[1], "r");
        if (stream == NULL)
        {
            std_error_dash();
            exit(EXIT_FAILURE);
        }
    }
    else if (argc > 2)
    {
        std_error_dash();
        exit(0);
    }

    while (1)
    {
        char *str = NULL;
        if (argc == 1)
        {
            // printf("%s\n",str);
            str = get_input_from_user();
            // printf("1.%s\n",str);
        }
        else
        {
            str = get_input_from_file(stream);
        }

        if (!str)
        {
            continue;
        }
        else
        {
            str = clean_whitespace(str);
            char *temp_path = run_main(str, path);

            // printf("%ld,%s\n",strlen(temp_path),temp_path);
            if (strlen(temp_path) > 1)
            {
                free(path);
                char *path __attribute__((unused));
                path = strdup(temp_path);
            }
        }
        free(str);
        // printf("6.%s\n", str);
    }
    return 0;
}
