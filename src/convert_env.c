#include "../headers/minishell.h"

char	**convert_env(t_mini *mini)
{
	// pour le moment ne fait que repasser l'env de base
	return (mini->env_start);
}

void	free_env(char **envp)
{
	//pour le moment fait rien, mais va free le truc plus tard
	ft_printf("on free le truc %s", envp[1]);
}
