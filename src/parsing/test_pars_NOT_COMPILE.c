/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_NOT_COMPILE.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/11 18:06:20 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

char	*take_fd(char	*str)
{
	int	i;
	int	count;
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

char	*change_cmd(char *str)
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
		if (str[i] == '>' && is_open % 2 == 0)
		{
			i++;
			while (str[i] == ' ')
				i++;
			while (str[i] != ' ')
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
		if (str[i] == '>' && is_open % 2 == 0)
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

int	main(int ac, char **av)
{
	char	*str;
	int		i;
	char	**fd_out;
	int		nb_fd_out;
	int		ct_fd_out;
	int		is_passed;
	int		is_open;

	nb_fd_out = 0;
	i = 0;
	is_open = 0;
	if (ac > 1)
		str = strdup(av[1]);
	if (!str)
		return(1);
	while (str && str[i])
	{
		if (str[i] == '"')
			is_open++;
		else if (str[i] == '>' && is_open % 2 == 0)
			nb_fd_out ++;
		i++;
	}
	i = 0;
	is_open = 0;
	if (nb_fd_out > 0)
	{
		fd_out = malloc(sizeof(char *) * (nb_fd_out + 1));
		if (!fd_out)
		is_passed = 0;
		ct_fd_out = 0;
		while (str && str[i] && ct_fd_out != nb_fd_out)
		{
			if (str[i] == '"')
				is_open++;
			else if (str[i] == '>' && is_open % 2 == 0)
			{
				while (str[i] == ' ')
					i++;
				fd_out[ct_fd_out] = take_fd(&str[i]);
				ct_fd_out++;
			}
			i++;
		}
		fd_out[ct_fd_out] = NULL;
	}
	i = 0;
	while (fd_out && fd_out[i])
	{
		printf("%s\n", fd_out[i]);
		free(fd_out[i]);
		i++;
	}
	str = change_cmd(str);
	printf("%s", str);
	free(fd_out);
	if (str)
		free(str);
	return (0);
}
