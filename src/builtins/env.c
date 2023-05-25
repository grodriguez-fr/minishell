#include "../../headers/minishell.h"

int env(t_mini *mini)
{
    printf("env : %s\n", mini->env->value);
    return (1);
} 
