/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:42:40 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 14:49:46 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	error(t_mini *mini, char *message)
{
	(void)mini;
	if (mini->env)
		clear_env(&mini->env, free);
	ft_putstr_fd(message, 2);
	exit(1);
}

void	clear_env(t_env_p **env, void (*del)(void*))
{
	t_env_p	*next;

	if (!env || ! del)
		return ;
	next = *env;
	while (next)
	{
		next = next->next;
		if ((*env)->key)
			del((*env)->key);
		if ((*env)->key)
			del((*env)->value);
		free(*env);
		*env = next;
	}
}
