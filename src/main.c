/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/05/28 19:05:52 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	struct sigaction	sa;
	sigset_t			mask;
	t_mini				mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	mini.ex = NULL;
    mini.command_return = 0;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, (void *)mini.env);
	parse_env(envp, &mini.env, mini);
	launch_minishell_img();
	prompt(mini);
	return (0);
}
