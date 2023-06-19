/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/06/12 15:40:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_command_ret;

void    init_signals(t_mini mini)
{
	struct sigaction	sa;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, (void *)mini.env);
	sigaction(SIGQUIT, &sa, (void *)mini.env);
    rl_catch_signals = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_mini				mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	mini.ex = NULL;
	g_command_ret = 0;
    init_signals(mini);
    //init_term(&mini);
	parse_env(envp, &mini.env, mini);
	//launch_minishell_img();
	prompt(mini);
	return (0);
}
