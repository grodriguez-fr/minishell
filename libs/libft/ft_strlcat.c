/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:40:20 by astachni          #+#    #+#             */
/*   Updated: 2022/11/23 21:27:31 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;
	size_t	dest_size;

	i = 0;
	if (!dest && size == 0)
		return (ft_strlen(src));
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dest);
	if (dest_size >= size)
		return (size + src_size);
	while (dest_size + i < size - 1 && src[i])
	{
		dest[dest_size + i] = (char)src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
	return (dest_size + src_size);
}
