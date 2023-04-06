/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:08:58 by astachni          #+#    #+#             */
/*   Updated: 2022/11/08 14:09:03 by astachni         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	atoi_test(char const *str)
{
	size_t	i;
	size_t	nb;
	size_t	neg;

	neg = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb * neg);
}

int	ft_atoi(char const *str)
{
	size_t		i;
	int			nb;
	int			neg;

	neg = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (atoi_test(str) == (size_t)-9223372036854775807L -1L)
		return (0);
	if (atoi_test(str) != (size_t)(nb * neg))
		return (-1);
	return (nb * neg);
}
