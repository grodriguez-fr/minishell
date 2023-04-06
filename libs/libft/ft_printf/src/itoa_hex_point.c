/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_hex_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni@student.42lyon.fr <astachni>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:47:26 by astachni@st       #+#    #+#             */
/*   Updated: 2022/12/01 20:36:46 by astachni@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	nbr(size_t n)
{
	int	i;

	i = 1;
	while (n >= 16)
	{
		n /= 16;
		i++;
	}
	return (i);
}

char	*itoa_hex_point(size_t n, char *base)
{
	char	*result;
	int		len;

	if (!base)
		return (NULL);
	len = nbr(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = 0;
	result[0] = '0';
	len--;
	while (n > 0)
	{
		result[len] = base[n % 16];
		n /= 16;
		len--;
	}
	return (result);
}
