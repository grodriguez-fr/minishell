/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:00:05 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/19 16:00:13 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"    

extern int	g_command_ret;

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
			ft_printf("Quit (core dumped)\n");
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
