#include "../../headers/minishell.h"

int exit_builtin(t_mini *mini, t_exec *ex)
{
    printf("exit env %s with %s\n", mini->env->value, ex->args[0]);
    return (1);
} 
