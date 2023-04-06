/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 15:02:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	parse_env(char **envp, t_mini **env);

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	parse_env(envp, &mini.env);
}

void	parse_env(char **envp, t_mini **env)
{
	int	i;

	i = 0;
}
