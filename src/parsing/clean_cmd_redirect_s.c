/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_redirect_s.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:23 by astachni          #+#    #+#             */
/*   Updated: 2023/07/14 13:41:03 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

char	*cpy_cmdf(char *new_str, char *str, char sep)
{
	size_t	i;
	int		count;
	size_t	is_open_s;
	size_t	is_open_d;

	i = 0;
	count = 0;
	is_open_s = 0;
	is_open_d = 0;
	while (str && i < ft_strlen(str))
	{
		is_open_s += is_open(str, i, is_open_d, '"');
		is_open_d += is_open(str, i, is_open_s, '\'');
		if (str[i] == sep && is_open_s % 2 == 0 && is_open_d % 2 == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_str[count++] = str[i++];
	}
	free(str);
	return (new_str);
}

char	*change_cmdf(char *str, char sep)
{
	char	*new_str;
	size_t	count;

	count = count_sep(str, sep);
	new_str = malloc(sizeof(char) * (count + 1));
	if (!new_str)
		return (NULL);
	new_str[count] = 0;
	new_str = cpy_cmdf(new_str, str, sep);
	return (new_str);
}

size_t	count_sep(char *str, char sep)
{
	size_t	is_open_s;
	size_t	is_open_d;
	size_t	i;
	size_t	count;

	is_open_s = 0;
	is_open_d = 0;
	i = 0;
	count = 0;
	while (str && i < ft_strlen(str))
	{
		is_open_s += is_open(str, i, is_open_d, '"');
		is_open_d += is_open(str, i, is_open_s, '\'');
		if (str[i] == sep && is_open_s % 2 == 0 && is_open_d % 2 == 0)
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
	return (count);
}
