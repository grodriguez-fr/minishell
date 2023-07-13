/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:04:31 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/13 15:44:36 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_if_key(t_env_p **start, char *key)
{
	t_env_p	*to_free;

	if (*start)
	{
		if (same_string((*start)->key, key))
		{
			to_free = *start;
			*start = (*start)->next;
			free(to_free->key);
			free(to_free->value);
			free(to_free);
		}
		else
			remove_if_key(&(*start)->next, key);
	}
}

//ca marche pas mais tkt
t_env_p	*is_null(t_env_p **env)
{
	if (!env || !*env)
		*env = NULL;
	return (*env);
}

int	unset(t_mini *mini, t_exec *ex)
{
	int	i;

	i = 1;
	if (!ex->args)
		return (1);
	while (ex->args[i])
		remove_if_key(&mini->env, ex->args[i++]);
	mini->env = is_null(&mini->env);
	return (0);
}
