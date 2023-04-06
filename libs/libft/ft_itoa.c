/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni@student.42lyon.fr <astachni>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:15:28 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/24 19:56:59 by astachni@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr(int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

static int	is_neg(char *str, int isneg, int len)
{
	if (isneg == 1)
		str[0] = '-';
	else
		len--;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		neg;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = n < 0;
	if (neg)
		n *= -1;
	len = nbr(n);
	str = malloc((len + (1 + neg)) * sizeof(char));
	if (!str)
		return (NULL);
	str[len + neg] = 0;
	len = is_neg(str, neg, len);
	while (n >= 10)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	str[len--] = n + '0';
	return (str);
}
