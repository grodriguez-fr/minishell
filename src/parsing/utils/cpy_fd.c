/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:09:28 by astachni          #+#    #+#             */
/*   Updated: 2023/06/13 18:59:06 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	is_open(char *str, int i, size_t is_open, char c)
{
	if (str[i] && str[i] == c && is_open % 2 == 0)
		return (1);
	return (0);
}

char	*cpy(char *str, char *fd, size_t i)
{
	size_t	count;
	size_t	is_open_d;
	size_t	is_open_s;

	is_open_d = 0;
	is_open_s = 0;
	count = 0;
	while (str && i < ft_strlen(str))
	{
		if (str[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		else if (str[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		else
			fd[count++] = str[i];
		i++;
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& i < ft_strlen(str) && ft_isspace(str[i]))
			break ;
	}
	fd[count] = '\0';
	return (fd);
}