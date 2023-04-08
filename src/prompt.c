/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/04/08 20:16:47 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompt(t_mini mini)
{
	char	*input;
	t_env_p	*env;

	env = mini.env;
	while (1)
	{
		while (env && ft_strncmp(env->key, "PWD", 3))
			env = env->next;
		input = readline(env->value);
		if (!input)
			exit_minishell(&mini);
		if (*input == '\0')
			continue ;
		add_history(input);
		mini = parse_and_exec(input, mini);
		ft_printf("your command: %s\n", input);
		if (input)
			free(input);
		free_cmd(&mini.ex, free);
	}
}

void	signal_handler(int sign)
{
	ft_printf("\n>> ");
}
