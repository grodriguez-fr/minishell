/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni@student.42lyon.fr <astachni>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:41:41 by astachni@st       #+#    #+#             */
/*   Updated: 2022/12/04 19:38:31 by astachni@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	verify_char(const char c)
{
	if (c == 's' || c == 'c' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || \
		c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		len_str;

	len_str = 0;
	count = 0;
	if (!str || write (1, "", 0) != 0)
		return (-1);
	va_start(args, str);
	while (str[len_str] != '\0')
	{
		if (str[len_str] == '%' && str[len_str + 1] == '\0')
			break ;
		if (verify_char(str[len_str + 1]) == 0 && str[len_str] == '%')
			len_str++;
		else if (str[len_str] != '%')
			count += write(1, &str[len_str], 1);
		else if (str[len_str] == '%')
			count += print_type(str[++len_str], args);
		len_str++;
	}
	va_end(args);
	return (count);
}
