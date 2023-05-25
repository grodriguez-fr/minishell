#include "../headers/minishell.h"

int is_builtin(char *cmd_name)
{
    if (!ft_memcmp(cmd_name, "echo", 4))
        return (1);
    if (!ft_memcmp(cmd_name, "cd", 2))
        return (1);
    if (!ft_memcmp(cmd_name, "pwd", 3))
        return (1);
    if (!ft_memcmp(cmd_name, "export", 6))
        return (1);
    if (!ft_memcmp(cmd_name, "unset", 5))
        return (1);
    if (!ft_memcmp(cmd_name, "env", 3))
        return (1);
    if (!ft_memcmp(cmd_name, "exit", 5))
        return (1);
    return (0);
}

int execute_builtin(t_mini *mini, t_exec *ex, char *cmd_name)
{
    ft_printf("execute une builtin\n");
    if (!ft_memcmp(cmd_name, "echo", 4))
        return (echo(ex, "test", 0), 1);
    if (!ft_memcmp(cmd_name, "cd", 2))
        return (cd(mini,  ex));
    if (!ft_memcmp(cmd_name, "pwd", 3))
        return (pwd(mini));
    if (!ft_memcmp(cmd_name, "export", 6))
        return (export(*mini, ex), 1);
    if (!ft_memcmp(cmd_name, "unset", 5))
        return (unset(mini, ex));
    if (!ft_memcmp(cmd_name, "env", 3))
        return (env(mini));
    if (!ft_memcmp(cmd_name, "exit", 5))
        return (exit_builtin(mini, ex));
    ft_printf("builtin inconnue??\n");
    return (0);
}

int builtin_env_modifier(char *cmd_name)
{
    if (!ft_memcmp(cmd_name, "cd", 2))
        return (1);
    if (!ft_memcmp(cmd_name, "export", 6))
        return (1);
    if (!ft_memcmp(cmd_name, "unset", 5))
        return (1);
    if (!ft_memcmp(cmd_name, "exit", 5))
        return (1);
    return (0);
}
