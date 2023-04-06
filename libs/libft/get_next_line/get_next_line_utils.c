/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:04:44 by astachni          #+#    #+#             */
/*   Updated: 2023/02/16 15:19:36 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = '\0';
		i++;
	}
}

size_t	ft_strlenn(char const *str)
{
	const char	*str_start;

	str_start = str;
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		str++;
	return (str - str_start);
}

size_t	ft_strcpy(char	*s1, char *s2)
{
	int	i;

	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			s2[i] = s1[i];
			i++;
		}
	}
	return (i);
}

char	*ft_strfjoin(char *s1, char const *buffer, int read_value)
{
	char	*str;
	int		i;
	int		j;
	size_t	s1_len;

	if (buffer == NULL)
		return (NULL);
	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlenn(s1);
	str = malloc(((s1_len + ft_strlenn(buffer) + 1) * sizeof(char)));
	if (str == NULL)
		return (NULL);
	i = ft_strcpy(s1, str);
	j = 0;
	while (buffer && buffer[j] && j < read_value && buffer[j] != '\n')
		str[i++] = buffer[j++];
	if (buffer[j] == '\n')
		str[i++] = '\n';
	str[i] = 0;
	if (s1)
		free(s1);
	return (str);
}
