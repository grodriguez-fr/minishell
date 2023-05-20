/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/05/20 18:02:18 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	prompt(t_mini mini)
{
	char	*input;
	t_env_p	*env;
	t_exec	*ex;
	int		i;

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
		ex = mini.ex;
		while (ex)
		{
			ft_printf("\ncomp pipe : %s\n", ex->comp_pipe);
			ft_printf("\ncmd name : %s\n", ex->cmd_name);
			i = 0;
			while (ex->args && ex->args[i])
				ft_printf("args : %s\n", ex->args[i++]);
			i = 0;
			while (ex->files_in && ex->files_in[i])
				printf("file in :< %s\n", ex->files_in[i++]);
			i = 0;
			while (ex->files_out && ex->files_out[i])
				printf("file out :> %s\n", ex->files_out[i++]);
			i = 0;
			while (ex->here_docs && ex->here_docs[i])
				printf("file heredocs :<< %s\n", ex->here_docs[i++]);
			i = 0;
			while (ex->files_out_a && ex->files_out_a[i])
				printf("file out append :>> %s\n", ex->files_out_a[i++]);
			ex = ex->next;
		}
		if (input)
			free(input);
		exec_all(&mini);
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
