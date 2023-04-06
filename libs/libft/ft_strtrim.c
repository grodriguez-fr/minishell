/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:55:28 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/20 20:40:10 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_comp(char const s, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static size_t	nb_trim_start(char const *s, char const *set)
{
	size_t	i;
	size_t	nbchar;

	nbchar = 0;
	i = 0;
	while (s[i] && char_comp(s[i++], set))
	{
		nbchar++;
	}
	return (nbchar);
}

static size_t	nb_trim_stop(char const *s, char const *set)
{
	size_t	i;

	i = ft_strlen(s);
	i--;
	while (s[i] && char_comp(s[i], set) && (int)i > 0)
	{
		i--;
	}
	i++;
	return (i);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	nb_start;
	size_t	nb_stop;

	if (s == NULL)
		return (NULL);
	nb_start = nb_trim_start(s, set);
	nb_stop = nb_trim_stop(s, set);
	return (ft_substr(s, nb_start, nb_stop - nb_start));
}
