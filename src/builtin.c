#include "../headers/minishell.h"

int is_builtin(char *cmd_name)
{
    if (ft_memcmp(cmd_name, "echo", 4))
        return (1);
    if (ft_memcmp(cmd_name, "cd", 2))
        return (1);
    if (ft_memcmp(cmd_name, "pwd", 3))
        return (1);
    if (ft_memcmp(cmd_name, "export", 6))
        return (1);
    if (ft_memcmp(cmd_name, "unset", 5))
        return (1);
    if (ft_memcmp(cmd_name, "env", 3))
        return (1);
    if (ft_memcmp(cmd_name, "exit", 5))
        return (1);
    return (0);
}

int execute_builtin(t_mini *mini, t_exec *ex, char *cmd_name)
{
    if (ft_memcmp(cmd_name, "echo", 4))
        return (echo(ex));
    if (ft_memcmp(cmd_name, "cd", 2))
        return (cd(ex));
    if (ft_memcmp(cmd_name, "pwd", 3))
        return (pwd(ex));
    if (ft_memcmp(cmd_name, "export", 6))
        return (export(ex));
    if (ft_memcmp(cmd_name, "unset", 5))
        return (unset(ex));
    if (ft_memcmp(cmd_name, "env", 3))
        return (env(ex));
    if (ft_memcmp(cmd_name, "exit", 5))
        return (exit_builtin(ex));
    ft_printf("builtin inconnue??\n");
    return (0);
} 
