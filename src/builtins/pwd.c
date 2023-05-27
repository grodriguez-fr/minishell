#include "../../headers/minishell.h"

int pwd(t_mini *mini)
{
    char    *res;

    res = get_env_value(mini, "PWD");
    if (!res)
        return (1);
    if (ft_printf("%s\n", res) == -1)
        return (1);
    return (0);
} 
