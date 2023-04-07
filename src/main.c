/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 12:42:05 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	char	*input;

	(void)ac;
	(void)av;
	mini.env = NULL;
	parse_env(envp, &mini.env);
	launch_minishell_img();
	while (1)
	{
		input = readline(">> ");
		if (!input || *input == '\0')
			continue ;
		add_history(input);
		ft_printf("your command: %s\n", input);
		if (input)
			free(input);
	}
	return (0);
}
