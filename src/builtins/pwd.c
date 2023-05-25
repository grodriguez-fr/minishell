#include "../../headers/minishell.h"

int pwd(t_mini *mini)
{
    printf("pwd : %s\n", mini->env->value);
    return (1);
} 
