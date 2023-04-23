/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/04/21 16:01:35 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompt(t_mini mini)
{
	char	*input;
	int		i;
	t_env_p	*env;
	t_exec	*ex;

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
		ex = mini.ex;
		while (ex)
		{
			ft_printf("%s ", ex->cmd_name);
			i = 0;
			while (ex->args && ex->args[i])
				ft_printf("%s ", ex->args[i++]);
			if (ex->next)
				ft_printf("| ");
			ex = ex->next;
		}
		ft_printf("\n");
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
