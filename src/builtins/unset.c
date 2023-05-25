#include "../../headers/minishell.h"

int unset(t_mini *mini, t_exec *ex)
{
    printf("unset %s to %s\n", mini->env->value, ex->args[0]);
    return (1);
} 
