#include "minishell.h"

void    write_not_found(char **new_env, char *name)
{
    free_env(new_env);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(name, 2);
    ft_putstr_fd(": command not found\n", 2);
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
