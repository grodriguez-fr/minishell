/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/07/14 13:57:59 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_exit(t_mini mini);

void	prompt(t_mini mini)
{
	int	i;

	while (1)
	{
		i = -1;
		get_to_display(&mini);
		mini.input = readline(mini.to_display);
		if (mini.to_display)
			free(mini.to_display);
		is_exit(mini);
		if (*(mini.input) == 0)
			continue ;
		add_history(mini.input);
		mini = parse_and_exec(mini.input, mini);
		while (mini.input && mini.input[++i] && mini.input[i] == ' ')
			;
		if (mini.input[i] && !mini.ex)
			ft_printf("PARSE ERROR\n");
		if (mini.input)
			free(mini.input);
		exec_all(&mini);
		free_cmd(&mini.ex, free);
	}
}

void	is_exit(t_mini mini)
{
	if (!mini.input)
	{
		ft_printf("exit\n");
		exit_minishell(&mini, 0);
	}
}
