/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_NOT_COMPILE.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/08 18:06:10 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../headers/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	**cpy(char *src, char **dest)
{
	int	i;
	int	is_open;
	int	j;
	int	c;

	is_open = 0;
	i = 0;
	j = 0;
	c = 0;
	while (src && src[i])
	{
		if (src[i] == '"')
			is_open++;
		if (is_open % 2 == 0 && src[i] == '|')
		{
			dest[c++] = ft_substr(&src[j], j, i - j);
			i++;
			j = i;
		}
		i++;
	}
	if (src[i] == 0)
		dest[c++] = ft_strdup(&src[j]);
	dest[c] = NULL;
	return (dest);
}

int	take_count(char *str, char sep, int count, int i)
{
	int	is_open;

	is_open = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ' && is_open % 2 == 0)
			i++;
		while (str[i] && str[i] == '"')
		{
			is_open++;
			i++;
		}
		if (str[i] == sep && is_open % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] == sep)
				return (count);
			count ++;
		}
		i++;
	}
	if (count > 0 && i > 0)
		count ++;
	return (count);
}

char	**ft_split_pipe(char *str, char sep)
{
	int		i;
	int		count;
	char	**to_return;

	i = 0;
	count = 0;
	count = take_count(str, sep, count, i);
	to_return = malloc(sizeof(char *) + (count + 1));
	if (!to_return)
		return (NULL);
	return (cpy(str, to_return));
}

int	main(void)
{
	const char	*str = "\"ec\"\"ho\" bonjour \"|\" abc avc | caca";

	return (0);
}
