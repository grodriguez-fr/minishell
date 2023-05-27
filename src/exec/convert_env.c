#include "../../headers/minishell.h"

static char	*env_part(char *key, char *value)
{
	int		len;
	int		i;
	int		k;
	char	*res;

    if (!value)
    {
        return (ft_strdup(key));
    }
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
	while(value[i])
		res[k++] = value[i++];
	res[k] = 0;
	return (res);
}

static int  len_env(t_mini *mini)
{
    int len;
	t_env_p	*current;
    
	current = mini->env;
	len = 1;
	while (current)
	{
		len++;
		current = current->next;
	}
    return (len); 
}

char	**convert_env(t_mini *mini)
{
	char	**res;
	int		i;
	t_env_p	*current;

	res = malloc(sizeof(char *) * len_env(mini));
	if (!res)
		return (NULL);
	current = mini->env;
	i = 0;
	while (current)
	{
		res[i++] = env_part(current->key, current->value);
        if (!res[i - 1])
            return (free_env(res), NULL);
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

void	free_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}
