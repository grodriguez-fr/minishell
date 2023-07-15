/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/07/15 14:30:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static char	**cpy_cmd(char *src, char **dest, int count, int j)
{
	size_t	i;
	size_t	is_open_d;
	size_t	is_open_s;
	int		c;

	is_open_d = 0;
	is_open_s = 0;
	i = -1;
	c = 0;
	while (src && ++i < ft_strlen(src) && count > c)
	{
		is_open_d += is_open(src, i, is_open_s, '"');
		is_open_s += is_open(src, i, is_open_d, '\'');
		if (is_open_s % 2 == 0 && is_open_d % 2 == 0 && src[i] == '|')
		{
			i = count_space(src, i);
			dest[c] = ft_substr(src, j, i - j);
			c++;
			i++;
			j = i;
		}
	}
	if (i <= ft_strlen(src) && src[i] == 0 && count > 0 && c < count)
		dest = cpy_last(dest, src, c, j);
	return (dest);
}

int	take_count(char *str, char sep, int count, int i)
{
	size_t	is_open_d;
	size_t	is_open_s;
	int		is_command;

	is_open_d = 0;
	is_open_s = 0;
	is_command = 0;
	while (str && i < (int)ft_strlen(str))
	{
		skip_quote(str, &i, &is_open_d, &is_open_s);
		if (str[i] && str[i] != ' ' && str[i] != sep
			&& str[i] != '<' && str[i] != '>')
			is_command = 1;
		else if (str[i] && str[i] == sep
			&& is_open_s % 2 == 0 && is_open_d % 2 == 0)
			if (ft_is_command(str, i, sep, &is_command))
				count ++;
		i++;
	}
	i = skip_space(i, str);
	if ((count > 0 || i > 0) && is_command == 1)
		count ++;
	if (is_command == 0 || is_open_d % 2 != 0 || is_open_s % 2 != 0)
		return (0);
	return (count);
}

char	**ft_split_pipe(char *str, char sep)
{
	int		count;
	char	**to_return;

	count = 0;
	to_return = NULL;
	count = take_count(str, sep, count, 0);
	if (count > 0)
	{
		to_return = malloc(sizeof(char *) * (count + 1));
		if (!to_return)
			return (NULL);
		to_return = cpy_cmd(str, to_return, count, 0);
		if (to_return)
			to_return[count] = NULL;
		else
			return (free_strs(to_return), NULL);
	}
	return (to_return);
}
