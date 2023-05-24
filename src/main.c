/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/05/24 16:31:53 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	// struct sigaction	sa;
	// sigset_t			mask;
	t_mini				mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	mini.ex = NULL;
	mini.env_start = envp;
	// sigemptyset(&mask);
	// sigaddset(&mask, SIGINT);
	// sigaddset(&mask, SIGQUIT);
	// sa.sa_handler = 0;
	// sa.sa_flags = SA_SIGINFO;
	// sa.sa_mask = mask;
	// sa.sa_sigaction = signal_handler;
	parse_env(envp, &mini.env, mini);
	// sigaction(SIGINT, &sa, (void *)mini.env);
	launch_minishell_img();
	prompt(mini);
	return (0);
}
