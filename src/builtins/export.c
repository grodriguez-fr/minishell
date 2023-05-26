/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:03:20 by astachni          #+#    #+#             */
/*   Updated: 2023/05/21 15:07:39 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int add_to_env(t_mini *mini, char *key, char *value)
{
	t_env_p	*current;
	t_env_p	*new_var;

    current = mini->env;
    while (current->next)
        current = current->next;

    new_var = malloc(sizeof(t_env_p));
    if (!new_var)
        return (0);
    current->next = new_var;
    new_var->next = NULL;
    new_var->key = ft_strdup(key);
    new_var->value = ft_strdup(value);
    return (1);
}

int replace_or_add(t_mini *mini, char *var)
{
	t_env_p	*current;
    char    **splited;
    int     ret;
    
    current = mini->env;
    splited = ft_split(var, '=');
    while (current)
    {
        if (!ft_strncmp(current->key, splited[0], \
            ft_strlen(current->key) + ft_strlen(splited[0])))
        {
            free(current->value);
            current->value = ft_strdup(splited[1]);
            return (free_split(splited), 1);
        }
        current = current->next;
    }
    ret = add_to_env(mini, splited[0], splited[1]);
    return (free_split(splited), ret);
}

int	export(t_mini *mini, t_exec *ex)
{
	t_env_p	*current;
    int     i;

	if (ex->args[1] == NULL)
	{
		current = mini->env;
		while (current)
		{
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		    current = current->next;
		}
	}
    i = 1;
    while (ex->args[i])
        if (!replace_or_add(mini, ex->args[i++]))
            return (0);
    return (1);
}
