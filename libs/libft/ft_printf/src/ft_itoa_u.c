/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni@student.42lyon.fr <astachni>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 22:14:19 by astachni@st       #+#    #+#             */
/*   Updated: 2022/11/29 18:19:39 by astachni@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static unsigned int	nbr(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa_u(unsigned int n)
{
	char				*str;
	unsigned int		len;

	len = nbr(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = 0;
	len --;
	while (n >= 10)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	str[len] = n + '0';
	return (str);
}
