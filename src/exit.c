/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:58:57 by astachni          #+#    #+#             */
/*   Updated: 2023/06/13 22:47:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_mini *mini, int code)
{
	if (mini->env)
		clear_env(&mini->env, free);
	clean_heredocs();
	rl_clear_history();
	free_cmd(&mini->ex, free);
	exit(code);
}
