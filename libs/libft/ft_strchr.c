/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:29:18 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/21 00:24:54 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *st, int c)
{
	int		i;
	char	*s;

	s = (char *)st;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&s[i]);
	return (0);
}
