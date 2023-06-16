#include "minishell.h"

int env(t_mini *mini)
{
    char    **envp;
    int     i;

    envp = convert_env(mini);
    i = 0;
    while (envp[i])
    {
        if (strchr(envp[i], '='))
            if (ft_printf("%s\n", envp[i]) == -1)
                return (free_env(envp), 1);
        i++;
    }
    return (free_env(envp), 0);
} 
