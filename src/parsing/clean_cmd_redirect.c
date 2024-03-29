/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:48:29 by astachni          #+#    #+#             */
/*   Updated: 2023/07/12 16:35:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	count_sep_here_append(char *str, char *sep);
char	*cpy_cmd(char *new_str, char *str, char *sep, size_t i);

char	*change_cmdf_here_append(char *str, char *sep)
{
	char	*new_str;
	ssize_t	count;

	count = count_sep_here_append(str, sep);
	new_str = NULL;
	if (count > 0)
	{
		new_str = malloc(sizeof(char) * (count + 1));
		if (!new_str)
			return (NULL);
		cpy_cmd(new_str, str, sep, 0);
	}
	free(str);
	return (new_str);
}

char	*cpy_cmd(char *new_str, char *str, char *sep, size_t i)
{
	int		count;
	size_t	is_open_d;
	size_t	is_open_s;

	is_open_d = 0;
	is_open_s = 0;
	count = 0;
	while (str && new_str && i < ft_strlen(str))
	{
		is_open_d += is_open(str, i, is_open_s, '"');
		is_open_s += is_open(str, i, is_open_d, '\'');
		if (str[i] == sep[0] && str[i + 1] == sep[1]
			&& is_open_s % 2 == 0 && is_open_d % 2 == 0)
		{
			i += 2;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_str[count++] = str[i++];
	}
	new_str[count] = 0;
	return (new_str);
}

ssize_t	count_sep_here_append(char *str, char *sep)
{
	size_t	is_open_s;
	size_t	is_open_d;
	size_t	i;
	size_t	count;

	is_open_s = 0;
	is_open_d = 0;
	i = -1;
	count = 0;
	while (str && ++i < ft_strlen(str))
	{
		is_open_d += is_open(str, i, is_open_s, '"');
		is_open_s += is_open(str, i, is_open_d, '\'');
		if (str[i + 1] && str[i] == sep[0] && str[i + 1] == sep[1]
			&& str[i + 2] && is_open_d % 2 == 0 && is_open_s % 2 == 0)
		{
			i += 2;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		count++;
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
	while (i > 0)
	{
		if (cmd[i] == '>')
			if (i != 0 && cmd[i - 1] == '>')
				return (1);
		if (cmd[i] == '<')
			if (i != 0 && cmd[i - 1] == '<')
				return (2);
		i--;
	}
	return (0);
}
