/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/05/31 18:04:01 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_mini mini)
{
	t_exec	*ex;
	int		i;

	while (1)
	{
		mini = get_to_display(mini);
		mini.input = readline(mini.to_display);
		if (mini.to_display)
			free(mini.to_display);
		if (!mini.input)
			exit_minishell(&mini, 0);
		else if (*(mini.input) == 0)
			continue ;
		add_history(mini.input);
		mini = parse_and_exec(mini.input, mini);
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
		if (mini.input)
			free(mini.input);
		exec_all(&mini);
		free_cmd(&mini.ex, free);
	}
}

void	signal_handler(int sign, siginfo_t *info, void	*context)
{
	char	pwd[256];
	char	*to_display;
	t_env_p	*env;
	int		i;

	(void)info;
	env = (t_env_p *)context;
	if (sign == SIGINT || sign == SIGQUIT)
	{
		if (getcwd(pwd, 256) != NULL)
		{
			i = 0;
			while (pwd[i])
				i++;
			while (pwd[i] != '/' && i >= 0)
				i--;
			i++;
			to_display = ft_strdup("\033[32m➜  \033[1m\033[35m");
			to_display = ft_strfjoin(to_display, &pwd[i]);
			to_display = ft_strfjoin(to_display, "\033[33m ✗ \033[0m");
			ft_printf("\n%s", to_display, env->value);
			free(to_display);
		}
	}
}
