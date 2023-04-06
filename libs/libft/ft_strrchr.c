/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:32:14 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/21 00:25:09 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len_str;

	len_str = ft_strlen(str);
	if ((char)c == 0)
		return ((char *)&str[ft_strlen(str)]);
	while ((int)len_str >= 0)
	{
		if (str[len_str] == (char)c)
			return ((char *)&str[len_str]);
		len_str--;
	}
	return (NULL);
}
