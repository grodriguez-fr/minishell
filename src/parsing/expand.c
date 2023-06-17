#include "minishell.h"

void replace_var(t_mini *mini, char **to_replace)
{
    t_env_p *env;

    env = mini->env;
    while (env)
    {
        if (same_string(env->key, &(*to_replace)[1]))
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

int ap_before(char *comm, int i)
{
    int j;

    j = i;
    while (j >= 0)
        if (comm[j--] == '\'')
            return (1);
    return (0);
}

int ap_after(char *comm, int i)
{
    int j;

    j = i;
    while (comm[j])
        if (comm[j++] == '\'')
            return (1);
    return (0); 
}

int should_expand(char *arg, char *comm)
{
    int found;

    found = ft_strstr(comm, arg);
    if (found == -1)
        return (0);
    return (!ap_before(comm, found) || !ap_after(comm, found));
}

char	**take_var(t_mini *mini, char *comm, char **args)
{
	int		i;

	if (!args || !mini)
		return (NULL);
	i = 0;
	while (args && args[i])
	{
		if (ft_strncmp(args[i], "$", 1) == 0 && should_expand(args[i], comm) && args[i][1])
            replace_var(mini, &args[i]);
		i++;
	}
	return (args);
}
