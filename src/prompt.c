/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 12:57:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompt(t_mini mini)
{
	char	*input;

	(void)mini;
	while (1)
	{
		input = readline(">> ");
		if (!input || *input == '\0')
			continue ;
		add_history(input);
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			if (input)
				free(input);
			exit(0);
		}
		if (input)
			free(input);
	}
}
