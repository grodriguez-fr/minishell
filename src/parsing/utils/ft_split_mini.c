/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/06/02 16:32:53 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	count_space(char *src, int i)
{
	while (src[i] && ft_isspace(src[i]))
		i++;
	return (i);
}

static char	**cpy_cmd(char *src, char **dest, int count, int j)
{
	int	i;
	int	is_open;
	int	c;

	is_open = 0;
	i = 0;
	c = 0;
	while (src && src[i] && count > c)
	{
		if (src[i] == '"' || src[i] == '\'')
			is_open++;
		if (is_open % 2 == 0 && src[i] == '|')
		{
			i = count_space(src, i);
			dest[c++] = ft_substr(src, j, i - j);
			i++;
			j = i;
		}
		i++;
	}
	if (src[i] == 0)
		dest[c] = ft_strdup(&src[j]);
	dest[count] = NULL;
	return (dest);
}

int	take_count(char *str, char sep, int count, int i)
{
	size_t	is_open_d;
	size_t	is_open_s;

	is_open_d = 0;
	is_open_s = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ' && is_open_d % 2 == 0
			&& is_open_s % 2 == 0)
			i++;
		if (str[i] && str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		else if (str[i] && str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else if (str[i] == sep && is_open_s % 2 == 0 && is_open_d % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] == sep)
				return (count);
			count ++;
		}
		if (str[i])
			i++;
	}
	if (count > 0 || i > 0)
		count ++;
	return (count);
}

char	**ft_split_pipe(char *str, char sep)
{
	int		count;
	char	**to_return;

	count = 0;
	count = take_count(str, sep, count, 0);
	to_return = malloc(sizeof(char *) * (count + 1));
	if (!to_return)
		return (NULL);
	to_return = cpy_cmd(str, to_return, count, 0);
	return (to_return);
}
