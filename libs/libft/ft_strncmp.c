/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:35:48 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/20 18:49:17 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *str1, char const *str2, size_t size)
{
	if (size > ft_strlen(str1))
		size = ft_strlen(str1) + 1;
	if (size > ft_strlen(str2))
		size = ft_strlen(str2) + 1;
	return (ft_memcmp(str1, str2, size));
}
