/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:58:57 by astachni          #+#    #+#             */
/*   Updated: 2023/04/08 20:21:17 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exit_minishell(t_mini *mini, int code)
{
	if (mini->env)
		clear_env(&mini->env, free);
    clean_heredocs();
	exit(code);
}
