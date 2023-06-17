#include "minishell.h"

void replace_var(t_mini *mini, char **to_replace)
{
    t_env_p *env;

    env = mini->env;
    while (env)
    {
        if (ft_strncmp(env->key, &(*to_replace)[1], ft_strlen(env->key)) == 0)
        {
            free(*to_replace);
            *to_replace = ft_strdup(env->value);
            return ;
        }
        env = env->next;
    }
    if ((*to_replace)[1] == '?' && !(*to_replace)[2])
    {
        free(*to_replace);
        *to_replace = ft_itoa(mini->command_ret);
        return ;
    }
    free(*to_replace);
    *to_replace = malloc(sizeof(char));
    (*to_replace)[0] = 0;
}

char	**take_var(t_mini *mini, char **args)
{
	int		i;

	if (!args || !mini)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		if (ft_strncmp(args[i], "$", 1) == 0)
            replace_var(mini, &args[i]);
		i++;
	}
	return (args);
}
