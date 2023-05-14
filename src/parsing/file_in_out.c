/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:03:19 by astachni          #+#    #+#             */
/*   Updated: 2023/05/14 18:54:52 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*in_out(t_exec *ex, char **fd, char *str, char sep);
char	**allocate_fd(char **fd, char *str, int nb_fd, char sep);
char	*take_fd(char *str);

t_mini	file_in_out(t_mini *mini)
{
	t_exec	*exec;

	exec = mini->ex;
	while (exec)
	{
		exec = in_out(exec, exec->files_out, exec->comp_pipe, '>');
		exec = in_out(exec, exec->files_in, exec->comp_pipe, '<');
		if (exec->next)
			exec = exec->next;
		else
			break ;
	}
	return (*mini);
}


t_exec	*in_out(t_exec *ex, char **fd, char *str, char sep)
{
	int	nb_fd;
	int	i;
	int	is_open;

	nb_fd = 0;
	i = 0;
	is_open = 0;
	if (!str || !ex)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == '"')
			is_open++;
		else if (str[i] == sep && is_open % 2 == 0)
			nb_fd ++;
		i++;
	}
	if (nb_fd > 0)
		fd = allocate_fd(fd, str, nb_fd, sep);
	if (sep == '>')
		ex->files_out = fd;
	else
		ex->files_in = fd;
	return (ex);
}

char	**allocate_fd(char **fd, char *str, int nb_fd, char sep)
{
	int	i;
	int	is_open;
	int	ct_fd;

	is_open = 0;
	i = 0;
	fd = malloc(sizeof(char *) * (nb_fd + 1));
	if (!fd)
		return (NULL);
	ct_fd = 0;
	while (str && str[i] && ct_fd != nb_fd)
	{
		if (str[i] == '"')
			is_open++;
		else if (str[i] == sep && is_open % 2 == 0)
		{
			while (str[i] && str[i] == ' ')
				i++;
			fd[ct_fd] = take_fd(&str[i]);
			ct_fd++;
		}
		i++;
	}
	fd[ct_fd] = NULL;
	return (fd);
}

char	*take_fd(char *str)
{
	int		i;
	int		count;
	char	*fd;

	i = 1;
	while (str && str[i] && str[i] == ' ')
		i++;
	count = 0;
	while (str && str[i] && str[i] != ' ')
	{
		i++;
		count++;
	}
	fd = malloc(sizeof(char) * (count + 1));
	i -= count;
	count = 0;
	while (str && str[i] && str[i] != ' ')
		fd[count++] = str[i++];
	fd[count] = '\0';
	return (fd);
}
