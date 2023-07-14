/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:00:05 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/14 12:44:59 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_command_ret;

void	init_signals(t_mini mini)
{
	struct sigaction	sa;
	sigset_t			mask;

	(void)mini;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
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
		to_display = ft_strdup("\001\033[31m➜  \033[1m\033[35m");
		to_display = ft_strfjoin(to_display, &pwd[i]);
		to_display = ft_strfjoin(to_display, "\033[33m ✗ \033[0m\002");
		rl_replace_line("", 0);
		ft_printf("^C\n");
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
	if (g_command_ret == -3)
		return ;
	if (g_command_ret == -2)
		exit(1);
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
