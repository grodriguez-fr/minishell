/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hear_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:29:29 by astachni          #+#    #+#             */
/*   Updated: 2023/06/02 16:31:33 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_fd_here_append(char **fd, char *str,
			size_t nb_fd, char *sep);
char	*take_fd_here_append(char *str);

char	**hear_append(char **fd, char *str, char *sep)
{
	size_t	nb_fd;
	size_t	i;
	size_t	is_open_s;
	size_t	is_open_d;

	nb_fd = 0;
	i = 0;
	is_open_s = 0;
	is_open_d = 0;
	if (!str)
		return (NULL);
	while (str && str[i] && str[i + 1])
	{
		if (i < ft_strlen(str) && str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		else if (i < ft_strlen(str) && str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else if (str[i] == sep[0] && str[i + 1] == sep[1]
			&& is_open_s % 2 == 0 && is_open_d == 0)
			nb_fd ++;
		i++;
	}
	if (nb_fd == 0)
		return (NULL);
	fd = allocate_fd_here_append(fd, str, nb_fd, sep);
	fd[nb_fd] = NULL;
	return (fd);
}

static char	**condition_to_take(char **fd, char *str,
	char *sep, size_t nb_fd)
{
	size_t	i;
	size_t	is_open_s;
	size_t	is_open_d;
	size_t	ct_fd;

	i = 0;
	is_open_s = 0;
	is_open_d = 0;
	ct_fd = 0;
	while (str && str[i] && str[i + 1] && ct_fd != nb_fd)
	{
		if (i < ft_strlen(str) && str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		if (i < ft_strlen(str) && str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else if (str[i] == sep[0] && str[i + 1] == sep[1]
			&& str[i + 2] && is_open_s % 2 == 0 && is_open_d % 2 == 0)
		{
			while (str[i] && str[i] == ' ')
				i++;
			fd[ct_fd] = take_fd_here_append(&str[i + 2]);
			ct_fd++;
		}
		i++;
	}
	fd[ct_fd] = NULL;
	return (fd);
}

char	**allocate_fd_here_append(char **fd, char *str, size_t nb_fd, char *sep)
{
	fd = malloc(sizeof(char *) * (nb_fd + 1));
	if (!fd)
		return (NULL);
	fd = condition_to_take(fd, str, sep, nb_fd);
	return (fd);
}

char	*take_fd_here_append(char *str)
{
	int		i;
	int		count;
	char	*fd;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	count = 0;
	while (str && str[i] && str[i] != ' ')
	{
		i++;
		count++;
	}
	fd = malloc(sizeof(char) * (count + 1));
	if (!fd)
		return (NULL);
	i -= count;
	return (cpy(str, fd, i));
}
