/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:48:29 by astachni          #+#    #+#             */
/*   Updated: 2023/05/25 14:38:44 by astachni         ###   ########.fr       */
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
	new_str = NULL;
	if (count > 0)
	{
		new_str = malloc(sizeof(char) * (count + 1));
		if (!new_str)
			return (NULL);
		i = 0;
		count = 0;
		is_open = 0;
		while (str && i < ft_strlen(str))
		{
			if (str[i] == '"')
				is_open++;
			else if (str[i] == sep[0] && str[i + 1] == sep[1]
				&& is_open % 2 == 0)
			{
				while (str[i] == sep[0])
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
	while (str && i < ft_strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i + 1] && str[i] == sep[0] && str[i + 1] == sep[1]
			&& str[i + 2] && is_open % 2 == 0)
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

int	take_last_redirect(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	i--;
	ft_printf("%s\n", &cmd[i]);
	while (i > 0)
	{
		if (cmd[i] == '>')
		{
			if (i != 0 && cmd[i - 1] == '>')
			{
				ft_printf("%d\n", 1);
				return (1);
			}
		}
		if (cmd[i] == '<')
			if (i != 0 && cmd[i - 1] == '<')
				return (2);
		i--;
	}
	ft_printf("%d-\n", 0);
	return (0);
}
