#include "../../headers/minishell.h"

int pwd(t_mini *mini)
{
    if (ft_printf("%s\n", get_env_value(mini, "PWD")) == -1)
        return (0);
    return (1);
} 
