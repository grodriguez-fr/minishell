/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:04:49 by astachni          #+#    #+#             */
/*   Updated: 2023/02/16 15:28:28 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define BASE_MIN "0123456789abcdef"
# define BASE_MAJ "0123456789ABCDEF"

int		ft_printf(const char *str, ...);
int		print_type(char c, va_list args);
int		verify_char(const char c);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
char	*ft_itoa_u(unsigned int n);
char	*itoa_hex(unsigned int n, char *base);
char	*itoa_hex_point(size_t n, char *base);
char	*ft_strdup(const char *src);

#endif
