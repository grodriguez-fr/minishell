#include "minishell.h"

int exit_error(char *file_name)
{
    ft_putstr_fd("minishell: ", 2);
    return (perror(file_name), 0);
}

int file_in(char **files)
{
    int fd;
    int i;

    i = 0;
    while (files && files[i])
    {
        fd = open(files[i], O_RDONLY);
        if (fd == -1) 
            return (exit_error(files[i]));
        close(fd);
        i++;
    }
    return (1);
}

int file_out(char **files)
{
    int fd;
    int i;

    i = 0;
    while (files && files[i])
    {
        fd = open(files[i], O_WRONLY | O_CREAT | O_APPEND);
        if (fd == -1)
            return (exit_error(files[i]));
        close (fd);
        i++;
    }
    return (1);
}

int check_redirection(t_exec *current)
{
    if (!file_out(current->files_out))
        return (0);
    if (!file_in(current->files_in))
        return (0);
    if (!file_out(current->files_out_a))
        return (0);
    return (1);
}
