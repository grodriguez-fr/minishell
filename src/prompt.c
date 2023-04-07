/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 17:46:07 by astachni         ###   ########.fr       */
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
		if (!input || *input == '\0')
			continue ;
		add_history(input);
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			if (input)
				free(input);
			exit_minishell(&mini);
		}
		ft_printf("your command: %s\n", input);
		if (input)
			free(input);
	}
}

void	signal_handler(int sign)
{
	ft_printf("\n>> ");
}
