/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:03:19 by astachni          #+#    #+#             */
/*   Updated: 2023/05/31 23:16:32 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_fd(char **fd, char *str, size_t nb_fd, char sep);
char	*take_fd(char *str);

char	**in_out(char **fd, char *str, char sep)
{
	size_t	nb_fd;
	size_t	i;
	size_t	is_open_d;
	size_t	is_open_s;

	nb_fd = 0;
	i = 0;
	is_open_s = 0;
	is_open_d = 0;
	if (!str)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		else if (str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else if (str[i] == sep && is_open_s % 2 == 0 && is_open_d % 2 == 0)
			nb_fd ++;
		i++;
	}
	if (nb_fd == 0)
		return (NULL);
	fd = allocate_fd(fd, str, nb_fd, sep);
	return (fd);
}

char	**allocate_fd(char **fd, char *str, size_t nb_fd, char sep)
{
	size_t	i;
	size_t	is_open_d;
	size_t	is_open_s;
	size_t	ct_fd;

	is_open_d = 0;
	is_open_s = 0;
	i = 0;
	fd = malloc(sizeof(char *) * (nb_fd + 1));
	if (!fd)
		return (NULL);
	ct_fd = 0;
	while (str && str[i] && ct_fd != nb_fd)
	{
		if (str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		else if (str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else if (str[i] == sep && is_open_s % 2 == 0 && is_open_d % 2 == 0)
		{
			while (str[i] && str[i] == ' ')
				i++;
			fd[ct_fd++] = take_fd(&str[i]);
		}
		i++;
	}
	fd[ct_fd] = NULL;
	return (fd);
}

static char	*cpy(char *str, char *fd, int i)
{
	size_t	count;
	size_t	is_open_d;
	size_t	is_open_s;

	is_open_d = 0;
	is_open_s = 0;
	count = 0;
	while (str && i < (int)ft_strlen(str))
	{
		if (str[i] == '"' && is_open_s % 2 == 0)
		{
			i++;
			is_open_d++;
		}
		else if (str[i] == '\'' && is_open_d % 2 == 0)
		{
			i++;
			is_open_s++;
		}
		fd[count++] = str[i++];
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& i < (int)ft_strlen(str) && ft_isspace(str[i]))
			break ;
	}
	fd[count] = '\0';
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
	if (!fd)
		return (NULL);
	i -= count;
	return (cpy(str, fd, i));
}
