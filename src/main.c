/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/04/13 13:37:06 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	dprintf(STDERR_FILENO, "%p\n", envp[0]);
	(void)ac;
	(void)av;
	mini.env = NULL;
	mini.ex = NULL;
	parse_env(envp, &mini.env, mini);
	signal(SIGINT, signal_handler);
	launch_minishell_img();
	prompt(mini);
	return (0);
}
