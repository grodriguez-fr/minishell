/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:07:38 by astachni          #+#    #+#             */
/*   Updated: 2023/07/14 16:10:22 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(int i, char *str)
{
	while (str && i < (int)ft_strlen(str) && ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_is_command(char *str, int i, char sep, int *is_command)
{
	if (*is_command == 0 || (str[i + 1] && str[i + 1] == sep))
		return (0);
	*is_command = 0;
	return (1);
}

int	count_space(char *src, int i)
{
	while (src[i] && ft_isspace(src[i]))
		i++;
	return (i);
}

int	*skip_quote(char *str, int *i, size_t *is_open_d, size_t *is_open_s)
{
	while (str[*i] && str[*i] == ' ' && *is_open_d % 2 == 0
		&& *is_open_s % 2 == 0)
			(*i)++;
		*is_open_d += is_open(str, *i, *is_open_s, '"');
		*is_open_s += is_open(str, *i, *is_open_d, '\'');
	return (i);
}

char	**cpy_last(char **dest, char *src, int c, int j)
{
	dest[c] = ft_strdup(&src[j]);
	if (!dest[c])
		return (free_strs(dest), NULL);
	return (dest);
}
