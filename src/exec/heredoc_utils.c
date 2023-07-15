/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:19:49 by astachni          #+#    #+#             */
/*   Updated: 2023/07/15 14:14:49 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_command_ret;

void	signal_handler_heredoc(int sign, siginfo_t *info, void	*context)
{
	(void)info;
	(void)context;
	if (sign == SIGQUIT)
	{
		printf("test");
		g_command_ret = 131;
		return ;
	}
}

void	init_signal(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = signal_handler_heredoc;
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
}

char	*heredoc_file_name(unsigned int nb)
{
	char	*res;
	char	*res2;

	res = ft_itoa(nb);
	if (!res)
		return (0);
	res2 = ft_strjoin("/tmp/.heredoc_tmp_file", res);
	if (!res2)
		return (free(res), NULL);
	return (free(res), res2);
}

int	open_heredoc(unsigned int i)
{
	char	*filename;
	int		fd;

	filename = heredoc_file_name(i);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (free(filename), fd);
}

int	res_null(char *res, char *word)
{
	if (!res && g_command_ret != 131)
	{
		ft_printf("\nbash: warning: here-document at line 1 delimited by\
end-of-file (wanted `%s')\n", word);
		return (1);
	}
	return (0);
}
