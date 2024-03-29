/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 22:38:08 by astachni@st       #+#    #+#             */
/*   Updated: 2023/07/12 16:35:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	nbr(unsigned int n)
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

char	*itoa_hex(unsigned int n, char *base)
{
	char	*result;
	int		len;

	if (!base)
		return (0);
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
