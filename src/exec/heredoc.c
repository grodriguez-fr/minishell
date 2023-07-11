/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:09:21 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/21 13:58:21 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int  g_command_ret;

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

int	heredoc_loop(t_mini *mini, t_exec *current, int i, int j)
{
	int		fd;
	char	*res;

	(void) mini;
	fd = open_heredoc(i);
	if (fd == -1)
		return (perror("Heredoc open fail"), 0);
	res = readline(">");
	while (!same_string(res, current->here_docs[j]))
	{
		if (write(fd, res, ft_strlen(res)) == -1)
			return (0);
		if (write(fd, "\n", 1) == -1)
			return (0);
		free(res);
		res = readline(">");
	}
	free(res);
    close(fd);
	return (1);
}

int heredoc_child(t_mini *mini)
{
	unsigned int	i;
	unsigned int	j;
	t_exec			*current;

	i = 0;
    g_command_ret = -2;
	current = mini->ex;
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

int change_heredoc_filenames(t_mini *mini, int pid)
{
    int     i;
    int     j;
    int     status;
    t_exec *current;

    g_command_ret = -3;
    i = 0;
    current = mini->ex;
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
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        //printf("fin : %d\n", status);
        if (status == 0)
        {
            g_command_ret = 130;
            rl_on_new_line();
            printf("^C\n");
            return (0);
        }
    }
    return (1);
}

int	heredoc(t_mini *mini)
{
    int pid;

    pid = fork();
    if (pid == -1)
        return (ft_putstr_fd("Fork failed for heredoc\n", 2), 0);
    else if (pid != 0)
        return (change_heredoc_filenames(mini, pid));
    else
        exit_minishell_nohd(mini, heredoc_child(mini));
    return (1);
}
