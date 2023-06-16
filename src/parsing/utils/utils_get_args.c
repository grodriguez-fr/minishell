/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:32:26 by astachni          #+#    #+#             */
/*   Updated: 2023/06/16 14:53:29 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_new_string(int size)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	return (new_str);
}

void	copy_argument(char *str, int start_index, char *new_str)
{
	size_t	i;
	size_t	j;
	size_t	is_open_d;
	size_t	is_open_s;

	i = 0;
	is_open_d = 0;
	is_open_s = 0;
	j = start_index;
	while (str && j < ft_strlen(str))
	{
		is_open_d += is_open(str, j, is_open_s, '"');
		is_open_s += is_open(str, j, is_open_d, '\'');
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& j < ft_strlen(str) && ft_isspace(str[j]))
			break ;
		if (str[j] != '\'' && str[j] != '"')
			new_str[i++] = str[j];
		j++;
	}
	new_str[i] = '\0';
}

char	*cpy_args(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*new_str;

	i = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	j = i;
	size = get_argument_size(str, j);
	new_str = allocate_new_string(size);
	if (!new_str)
		return (NULL);
	copy_argument(str, j, new_str);
	return (new_str);
}
