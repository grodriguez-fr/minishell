/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:56:15 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/19 18:46:25 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*alloc;

	if (size != 0)
		if (count > SIZE_MAX / size)
			return (0);
	alloc = malloc(count * size);
	if (alloc == NULL)
	{
		return (NULL);
	}
	if (count > 0 && size > 0)
		ft_bzero(alloc, count * size);
	return (alloc);
}
