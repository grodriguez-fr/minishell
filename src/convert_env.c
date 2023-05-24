#include "../headers/minishell.h"

char	*env_part(char *key, char *value)
{
	int		len;
	int		i;
	int		k;
	char	*res;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	res = malloc(sizeof(char) *len);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while(key[i])
		res[k++] = key[i++];
	i = 0;
	res[k++] = '=';
	while(key[i])
		res[k++] = value[i++];
	res[k] = 0;
	return (res);
}

char	**convert_env(t_mini *mini)
{
	char	**res;
	int		len;
	int		i;
	t_env_p	*current;

	current = mini->envp;
	len = 1
	while (current)
	{
		len++;
		current = current->next;
	}
	res = malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	current = mini->envp;
	i = 0;
	while (current)
	{
		res[i++] =env_part(current->key, current->value);
		current = current->next;
	}
	res[i] = NULL;
	//return (res);
	
	// pour le moment ne fait que repasser l'env de base
	return (mini->env_start);
}

void	free_env(char **envp)
{
	//pour le moment fait rien, mais va free le truc plus tard
	ft_printf("on free le truc %s", envp[1]);
}

