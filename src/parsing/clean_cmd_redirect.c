/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:48:29 by astachni          #+#    #+#             */
/*   Updated: 2023/05/16 17:40:09 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

ssize_t	count_sep_here_append(char *str, char *sep);

char	*change_cmdf_here_append(char *str, char *sep)
{
	char	*new_str;
	size_t	i;
	size_t	is_open;
	ssize_t	count;

	count = count_sep_here_append(str, sep);
	ft_printf("%d, %s\n", count, str);
	new_str = NULL;
	if (count > 0)
	{
		new_str = malloc(sizeof(char) * (count + 1));
		if (!new_str)
			return (NULL);
		i = 0;
		count = 0;
		is_open = 0;
		while (str && i + 1 < ft_strlen(str))
		{
			if (str[i] == '"')
				is_open++;
			if (str[i] == sep[0] && str[i + 1] == sep[1] && is_open % 2 == 0)
			{
				i++;
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && str[i] != ' ')
					i++;
			}
			new_str[count++] = str[i++];
		}
		new_str[count] = 0;
	}
	free(str);
	return (new_str);
}

ssize_t	count_sep_here_append(char *str, char *sep)
{
	size_t	is_open;
	size_t	i;
	size_t	count;

	is_open = 0;
	i = 0;
	count = 0;
	while (str && i + 1 < ft_strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep[0] && str[i + 1] == sep[1] && is_open % 2 == 0)
		{
			i += 2;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		count++;
		i++;
	}
	return (count);
}
