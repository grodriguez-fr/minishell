/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:24:22 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/20 01:29:05 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char			*dest;
	const size_t	len = ft_strlen((char *)src);

	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_memcpy(dest, src, (size_t)len);
	dest[len] = '\0';
	return (dest);
}
