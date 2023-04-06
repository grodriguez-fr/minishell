/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:42:40 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 16:35:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	error(t_mini mini)
{
	(void)mini;
}

void	clear_lst(t_env_p **env, void (*del)(void*))
{
	t_env_p 	*next;

	if (!env || ! del)
		return ;
	next = *env;
	while (next)
	{
		next = next->next;
		del((*env)->key);
		del((*env)->value);
		free(*env);
		*env = next;
	}
}
