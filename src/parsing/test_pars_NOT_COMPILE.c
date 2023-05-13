/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_NOT_COMPILE.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/13 16:40:18 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

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

char	*change_cmd(char *str, char sep)
{
	char	*new_str;
	int		i;
	int		is_open;
	int		count;

	i = 0;
	count = 0;
	is_open = 0;
	while (str && i < strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		count++;
		i++;
	}
	new_str = malloc(sizeof(char) * (count + 1));
	i = 0;
	count = 0;
	is_open = 0;
	while (str && i < strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] == ' ')
				i++;
			while (str[i] != ' ')
				i++;
		}
		new_str[count++] = str[i++];
	}
	new_str[count] = 0;
	return (new_str);
}

char	**allocate_fd(char **fd, char *str, int nb_fd, char sep)
{
	int	i;
	int	is_passed;
	int	is_open;
	int	ct_fd;

	is_open = 0;
	i = 0;
	fd = malloc(sizeof(char *) * (nb_fd + 1));
	if (!fd)
		return (NULL);
	is_passed = 0;
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

int	main(int ac, char **av)
{
	return (0);
}
