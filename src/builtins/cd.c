#include "../../headers/minishell.h"

int cd(t_mini *mini, t_exec *ex)
{
    printf("cd from %s to %s\n", mini->env->value, ex->args[0]);
    return (1);
} 
