#include "minishell.h"

void    write_not_found(char **new_env, char *name)
{
    char    *to_write;
    char    *buffer;

    free_env(new_env);
    buffer = ft_strjoin("minishell: ", name);
    to_write = ft_strjoin(buffer, ": command not found\n");
    free(buffer);
    ft_putstr_fd(to_write, 2);
    exit(127);
}

void    exit_errno(int ret)
{
    if (ret == -1 && errno == 22)
        exit(127);
    if (ret == -1 && errno == 13)
        exit(126);
    exit(ret);
}
