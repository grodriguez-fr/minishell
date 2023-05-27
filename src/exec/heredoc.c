/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:09:21 by gurodrig          #+#    #+#             */
/*   Updated: 2023/05/16 11:09:23 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/minishell.h"

char    *heredoc_file_name(unsigned int nb)
{
    char    *res;
    char    *res2;

    res = ft_itoa(nb);
    if (!res)
        return (0);
    res2 = ft_strjoin("hd/doc", res);
    free(res);
    return (res2);
}

int	open_heredoc(unsigned int i)
{
	char	*filename;
    int     fd;

	filename = heredoc_file_name(i);
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
    free(filename);
    return (fd);
}

int    heredoc_loop(t_exec *current, int i, int j)
{
    int     fd;
    char    *res;

    fd = open_heredoc(i);
    if (fd == -1)
        return (0);
    res = readline(">");
    while (ft_strncmp(res, current->here_docs[j], ft_strlen(res)))
    {
        write(fd, res, ft_strlen(res));
        write(fd, "\n", 1);
        free(res);
        res = readline(">");
    }
    free(res);
    free(current->here_docs[j]);
    current->here_docs[j] = heredoc_file_name(i);
    return (1);
}

int heredoc(t_mini *mini)
{
	unsigned int	i;
	unsigned int	j;
	t_exec		*current;

	i = 1;
	current = mini->ex;
	while (current)
	{
        j = 0;
		while (current->here_docs && current->here_docs[j])
            heredoc_loop(current, i++, j++);
		current = current->next;
	}
	return (0);
}
