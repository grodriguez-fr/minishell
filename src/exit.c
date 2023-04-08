/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:58:57 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 22:46:34 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exit_minishell(t_mini *mini)
{
	if (mini->ex)
		free_cmd(&mini->ex, free);
	if (mini->env)
		clear_env(&mini->env, free);
	exit(0);
}
