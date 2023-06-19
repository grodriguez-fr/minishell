/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/06/18 22:16:28 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_command_ret;

void	prompt(t_mini mini)
{
	int	i;

	while (1)
	{
		i = -1;
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

void	write_prompt(char *to_display)
{
	int		i;
	char	pwd[256];

	if (getcwd(pwd, 256) != NULL)
	{
		i = 0;
		while (pwd[i])
			i++;
		while (pwd[i] != '/' && i >= 0)
			i--;
		i++;
		to_display = ft_strdup("\033[31m➜  \033[1m\033[35m");
		to_display = ft_strfjoin(to_display, &pwd[i]);
		to_display = ft_strfjoin(to_display, "\033[33m ✗ \033[0m");
		rl_replace_line("", 0);
		printf("^C\n");
		rl_set_prompt(to_display);
		rl_on_new_line();
		rl_redisplay();
		free(to_display);
		ft_bzero(pwd, 256);
	}
}

void	signal_handler(int sign, siginfo_t *info, void	*context)
{
	char	*to_display;

	(void)info;
	(void)context;
	to_display = NULL;
	if (sign == SIGQUIT)
	{
		if (g_command_ret == -1)
		{
			ft_printf("Quit\n");
			g_command_ret = 131;
		}
		return ;
	}
	if (g_command_ret != -1 && sign == SIGINT)
		write_prompt(to_display);
	else if (g_command_ret == -1 && sign == SIGINT)
		ft_printf("\n");
	g_command_ret = 130;
}
