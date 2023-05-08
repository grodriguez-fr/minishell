/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/05/08 18:21:53 by astachni         ###   ########.fr       */
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
		add_history(input);
		mini = parse_and_exec(input, mini);
		mini = file_in_out(mini);
		if (input)
			free(input);
		free_cmd(&mini.ex, free);
	}
}

void	signal_handler(int sign)
{
	char	*pwd;

	if (sign == SIGINT)
	{
		pwd = getenv("PWD");
		ft_printf("\n%s: ", pwd);
	}
}
