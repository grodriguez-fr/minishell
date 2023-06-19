/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/06/19 13:20:46 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_command_ret;

int	main(int ac, char **av, char **envp)
{
	t_mini				mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	mini.ex = NULL;
	g_command_ret = 0;
	init_signals(mini);
	parse_env(envp, &mini.env, mini);
	//launch_minishell_img();
	prompt(mini);
	return (0);
}
