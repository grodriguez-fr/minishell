/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:04:55 by astachni          #+#    #+#             */
/*   Updated: 2023/02/16 15:29:52 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	ft_strlenn(char const *str);
void	ft_bzero(char *str);
char	*ft_strfjoin(char *s1, char const *buffer, int read_value);
size_t	take_read(char *str, char *buffer, int read_buffer, size_t read_value);

#endif