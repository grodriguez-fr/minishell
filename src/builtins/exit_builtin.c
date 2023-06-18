#include "minishell.h"

int is_numeric(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    if (c == '-')
        return (1);
    if (c == '+')
        return (1);
    return (0);
}

int is_str_numeric(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (!is_numeric(str[i++]))
            return (0);
    return (1);
}

int nb_arg(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i - 1);
}

int exit_builtin(t_mini *mini, t_exec *ex)
{
    if (nb_arg(ex->args) == 0)
    {
        ft_printf("exit\n");
        exit_minishell(mini, 0);
    }
    else
    {
        if (is_str_numeric(ex->args[1]))
        {
            if (nb_arg(ex->args) > 1)
                return (ft_putstr_fd("minishell: exit: too many arugments\n", 1), 1);
            ft_printf("exit\n");
            exit_minishell(mini, ft_atoi(ex->args[1]));
        }
        ft_putstr_fd("minishell: exit: numeric argument required\n", 1);
        ft_printf("exit\n");
        exit_minishell(mini, 2);
    }
    return (0);
} 
