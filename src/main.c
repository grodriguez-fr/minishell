/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/05/25 17:20:47 by astachni         ###   ########.fr       */
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
	// sigemptyset(&mask);
	// sigaddset(&mask, SIGINT);
	// sigaddset(&mask, SIGQUIT);
	// sa.sa_handler = 0;
	// sa.sa_flags = SA_SIGINFO;
	// sa.sa_mask = mask;
	// sa.sa_sigaction = signal_handler;
	parse_env(envp, &mini.env, mini);
	t_env_p	*env = mini.env;
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	// sigaction(SIGINT, &sa, (void *)mini.env);
	launch_minishell_img();
	prompt(mini);
	return (0);
}
