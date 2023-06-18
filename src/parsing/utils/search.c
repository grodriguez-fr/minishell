/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:30:02 by astachni          #+#    #+#             */
/*   Updated: 2023/06/18 16:30:05 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;
	int			i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == *needle)
		{
			h = haystack;
			n = needle;
			while (*n && *h == *n)
			{
				h++;
				n++;
			}
			if (*n)
				return (i);
		}
		i++;
	}
	return (-1);
}
