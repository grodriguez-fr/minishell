/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/09 18:32:29 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*alloc_fd_out(char *src, char *dest, ssize_t start, ssize_t size)
{
	int	to_cpy;
	int	is_open;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * (size + 1));
	to_cpy = 0;
	is_open = 0;
	while (src[start] && size > to_cpy)
	{
		while (src[start] == '"')
		{
			start++;
			is_open++;
		}
		if (src[start] == ' ' && is_open % 2 == 0)
			break ;
		dest[to_cpy++] = src[start++];
	}
	dest[to_cpy] = 0;
	return (dest);
}

char	*get_new_str(char *str, int start, int end)
{
	char	*new_str;
	int		i;

	i = 0;
	printf("%ld, %d, %d\n", (strlen(str) - (end - start)), start, end);
	return (new_str);
}

int	main(int ac, char **av)
{
	char	*str;
	char	*redirect;
	char	*new_str;
	int		is_open;
	int		i;
	int		j;
	int		temp_i;
	int		to_malloc;

	if (ac > 1)
		str = strdup(av[1]);
	is_open = 0;
	i = 0;
	while (str && str[i] && !redirect)
	{
		while (str[i] == '"')
		{
			is_open++;
			i++;
		}
		if (str[i] == '>' && is_open % 2 == 0)
		{
			to_malloc = 0;
			i++;
			temp_i = i;
			while (ft_isspace(str[i]))
				i++;
			j = 0;
			while (str[i])
			{
				while (str[i] == '"')
				{
					j++;
					i++;
					is_open++;
				}
				if (str[i] == ' ' && is_open % 2 == 0)
				{
					redirect = alloc_fd_out(str, redirect, i - j, to_malloc);
					break ;
				}
				to_malloc++;
				i++;
				j++;
			}
		}
		i++;
	}
	get_new_str(str, temp_i, temp_i + j);
	printf("%s\n", redirect);
	printf("%s\n", str);
	if (str)
		free(str);
	return (0);
}
