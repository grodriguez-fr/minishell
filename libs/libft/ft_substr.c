/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni@student.42lyon.fr <astachni>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:56 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/24 19:39:49 by astachni@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		dest = malloc(sizeof(char));
		if (!dest)
			return (NULL);
		*dest = '\0';
		return (dest);
	}
	if (ft_strlen(s) - start > len)
		i = len + 1;
	else
		i = ft_strlen(s) - start + 1;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s + start, i);
	return (dest);
}
