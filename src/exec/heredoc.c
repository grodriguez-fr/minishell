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
#include "minishell.h"

char    *heredoc_file_name(unsigned int nb)
{
    char    *res;
    char    *res2;

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
    int     fd;

	filename = heredoc_file_name(i);
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
    return (free(filename), fd);
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
        if (write(fd, res, ft_strlen(res)) == -1)
            return (0);
        if (write(fd, "\n", 1) == -1)
            return (0);
        free(res);
        res = readline(">");
    }
    free(res);
    free(current->here_docs[j]);
    current->here_docs[j] = heredoc_file_name(i);
    if (!current->here_docs[j])
        return (0);
    return (1);
}

int heredoc(t_mini *mini)
{
	unsigned int	i;
	unsigned int	j;
	t_exec		*current;

	i = 0;
	current = mini->ex;
	while (current)
	{
        j = 0;
		while (current->here_docs && current->here_docs[j])
        {
            if (!heredoc_loop(current, i++, j++))
            {
                return (0);
            }
        }
		current = current->next;
	}
	return (1);
}

int    clean_heredocs()
{
    DIR             *dir;
    struct dirent   *entry;
    char            *path;

    dir = opendir("/tmp");
    if (!dir)
        return (0);

    entry = readdir(dir);
    while (entry)
    {
        if (!strncmp(entry->d_name, ".heredoc_tmp_file", 17))
        {
            path = ft_strjoin("/tmp/", entry->d_name);
            if (!path)
                return (0);
            if (unlink(path))
                perror("minishell: file suppression");
            free(path);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return (1);
}
