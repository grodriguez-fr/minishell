/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:39:49 by marvin@42.f       #+#    #+#             */
/*   Updated: 2023/02/25 14:37:33 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_str(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
		}
		if (s[i])
		{
			i++;
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

static void	ft_free(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
}

static int	ft_strs_plit(char const *s, char **dest, char c, int index)
{
	int	index_dest;
	int	first_char;

	index_dest = 0;
	while (s[index])
	{
		while (s[index] == c && s[index])
			index++;
		first_char = index;
		while (s[index] != c && s[index])
			index++;
		if (index != first_char)
		{
			dest[index_dest] = ft_substr(s, first_char, index - first_char);
			if (!dest[index_dest])
			{
				ft_free(dest, index_dest);
				return (-1);
			}
			index_dest++;
		}
	}
	dest[index_dest] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = malloc((nb_str(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	if (ft_strs_plit(s, dest, c, 0) == -1)
		return (NULL);
	return (dest);
}
