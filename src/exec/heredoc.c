/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:09:21 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/15 13:26:38 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_command_ret;

int	heredoc_loop(t_mini *mini, t_exec *current, int i, int j)
{
	int		fd;
	char	*res;
	char	*word;

	(void) mini;
	fd = open_heredoc(i);
	if (fd == -1)
		return (perror("Heredoc open fail"), 0);
	word = ft_strjoin(current->here_docs[j], "\n");
	res = get_next_line(STDIN_FILENO);
	if (res_null(res, current->here_docs[j]))
		return (free(word), free(res), close(fd), 1);
	while (!same_string(res, word))
	{
		if (write(fd, res, ft_strlen(res)) == -1)
			return (0);
		free(res);
		res = get_next_line(STDIN_FILENO);
		if (res_null(res, current->here_docs[j]))
			break ;
	}
	close(fd);
	return (free(word), free(res), 1);
}

int	heredoc_child(t_mini *mini)
{
	unsigned int	i;
	unsigned int	j;
	t_exec			*current;

	i = 0;
	g_command_ret = -2;
	current = mini->ex;
	init_signal();
	while (current)
	{
		j = 0;
		while (current->here_docs && current->here_docs[j])
		{
			if (!heredoc_loop(mini, current, i++, j++))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

void	take_current(t_exec *current, int i)
{
	int	j;

	while (current)
	{
		j = 0;
		while (current->here_docs && current->here_docs[j])
		{
			free(current->here_docs[j]);
			current->here_docs[j++] = heredoc_file_name(i++);
		}
		current = current->next;
	}
}

int	change_heredoc_filenames(t_mini *mini, int pid)
{
	int		i;
	int		status;
	t_exec	*current;

	g_command_ret = -3;
	i = 0;
	current = mini->ex;
	take_current(current, i);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_command_ret = WEXITSTATUS(status);
	else
	{
		printf("\n");
		g_command_ret = 130;
	}
	return (g_command_ret != 130);
}

int	heredoc(t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("Fork failed for heredoc\n", 2), 0);
	else if (pid != 0)
		return (change_heredoc_filenames(mini, pid));
	else
		exit_minishell_nohd(mini, heredoc_child(mini));
	return (1);
}
