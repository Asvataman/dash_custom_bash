#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "tokenizer.h"
#include "errorHandler.h"
#include "utils.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern void std_error_dash(void);

void run_exit(char *command)
{
    // function to implement exit
    int params_count = 0;
    params_count = get_params_count(command);
    if (params_count == 0)
    {
        exit(0);
    }
    else
    {
        std_error_dash();
    }
    return;
}

char *run_path(char *command, char *path)
{
    // function to implement path

    // printf("Initital Path - %s\n", path);
    int params_count = -1;
    char *temp_command = strdup(command);
    params_count = get_params_count(temp_command);
    // printf("Params Count = %d\n",params_count);

    if (params_count == 0)
    {
        path = "";
        return path;
    }
    else
    {
        char **params, *temp_path;
        int i, len = 0;

        params = get_params(command, params_count);

        for (i = 0; i < params_count; i++)
        {
            len += strlen(params[i]) + 1;
        }

        temp_path = (char *)malloc(1 + len * sizeof(char));
        strcpy(temp_path, "");

        for (i = 0; i < params_count; i++)
        {
            temp_path = strcat(temp_path, params[i]);
            temp_path = strcat(temp_path, ":");
        }
        return temp_path;
    }
}

void run_cd(char *command)
{
    // function to implement cd

    int params_count = -1;
    char *temp_command = strdup(command);
    params_count = get_params_count(temp_command);

    if (params_count == 1)
    {
        char **params;
        int status;
        params = get_params(command, params_count);

        status = chdir(params[0]);
        if (status == -1)
        {
            std_error_dash();
        }
        return;
    }
    else
    {
        std_error_dash();
        return;
    }
}

void run_command_to_stdout(char *command, char *path)
{
    char *dir, *saveptr;
    char full_path[1024];
    char **command_args;
    int params_count = get_params_count(command) + 1;

    command_args = (char **)malloc(sizeof(char *) * (params_count + 1));
    command_args = get_args(command);
    // printf("4.%s\n",command);

    char *token = strtok(command, " ");
    char *path_copy = strdup(path);
    dir = strtok_r(path_copy, ":", &saveptr);
    // printf("3.%s\n", command);

    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, token);
        // printf("%s\n", full_path);
        execv(full_path, command_args);
        dir = strtok_r(NULL, ":", &saveptr);
    }

    std_error_dash();
    _exit(EXIT_FAILURE);
}

void run_command_to_file(char *command, char *path)
{
    char *dir, *saveptr;
    char full_path[1024];
    char *output_file;
    char **command_args;

    char *redirection = strchr(command, '>');

    *redirection = '\0'; // spliting actual command and redirection
    output_file = redirection + 1;

    output_file = clean_whitespace(output_file);

    command_args = get_args(command);

    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // opening file, creating if does not exist, trucating if exist
    if (fd == -1)
    {
        std_error_dash();
        _exit(EXIT_FAILURE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1) // redirecting stdout to file.
    {
        std_error_dash();
        _exit(EXIT_FAILURE);
    }
    close(fd);

    dir = strtok_r(path, ":", &saveptr);

    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command_args[0]);
        execv(full_path, command_args);
        dir = strtok_r(NULL, ":", &saveptr);
    }

    // this should not execute if execv runs
    std_error_dash();
    _exit(EXIT_FAILURE);
}

void execute_command(char *command, char *path)
{
    // This function will be invoked by a child.
    // The function checks for redirection and calls respective function

    int redir_flag = 0;
    command = clean_whitespace(command);
    redir_flag = check_redirection(command);
    // printf("1.%d\n", redir_flag);
    // printf("%s\n",command);

    if (redir_flag == -1)
    {
        // printf("hbehe\n");
        std_error_dash();
    }
    else if (redir_flag == 0)
    {
        // printf("2.%s\n", command);
        run_command_to_stdout(command, path); // function to run command and output will be displayed in stdout
    }
    else if (redir_flag == 1)
    {
        run_command_to_file(command, path); // function to run command and redirect it to a file
    }
    // printf("jksanius\n");
    _exit(EXIT_FAILURE);
}

void run_from_path(char *command_line, char *path)
{
    // function to implement exit

    char *temp_command_line, *saveptr_command;
    int pid = 0;
    temp_command_line = strdup(command_line);

    if (*temp_command_line == '&')
    {
        std_error_dash();
    }
    else
    {
        char *command;
        command = strtok_r(command_line, "&", &saveptr_command); // Parse each command line into commands
        while (command != NULL)
        {
            pid = fork();
            if (pid == 0)
            {
                execute_command(command, path); // command is executed in the child and exited
            }
            else
            {
                wait(NULL);
                command = strtok_r(NULL, "&", &saveptr_command);
            }
        }
        free(command);
    }

    free(temp_command_line);
    
    return;
}

char *run_main(char *str, char *path)
{
    char *command_line = strdup(str);
    str = clean_whitespace(str);
    // printf("%s\n%ld", str, strlen(str));

    if (strlen(str) == 0)
    {
        // printf("%s\n%ld\n", str, strlen(str));ex
        free(command_line);
        return "0";
    }

    char *func_grp = strtok(str, " ");
    // printf("%s\n", func_grp);

    if (func_grp == NULL)
    {
        free(command_line);
        return "0";
    }

    if (strcmp(func_grp, "path") == 0)
    {

        return run_path(command_line, path);
        free(command_line);
    }
    else if (strcmp(func_grp, "cd") == 0)
    {
        // printf("%s\n",command);
        run_cd(command_line);
        char *ret = "0";
        free(command_line);
        return ret;
    }
    else if (strcmp(func_grp, "exit") == 0)
    {

        run_exit(command_line);
    }
    else
    {
        // printf("x.%s\n", func_grp);
        run_from_path(command_line, path);
        free(command_line);
        return "0";
    }

    return "0";
}