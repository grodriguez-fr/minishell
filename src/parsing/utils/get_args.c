/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:34:38 by astachni          #+#    #+#             */
/*   Updated: 2023/06/12 16:35:11 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word(char *cmd)
{
	int	i;
	int	count;
	int	is_open_d;
	int	is_open_s;

	i = 0;
	count = 0;
	is_open_d = 0;
	is_open_s = 0;
	while (cmd && i < (int)ft_strlen(cmd))
	{
		if (!ft_isspace(cmd[0]) && i == 0)
			count++;
		if (cmd[i] && ft_isspace(cmd[i]) == 1
			&& is_open_d % 2 == 0 && is_open_s % 2 == 0)
			count ++;
		if (i < (int)ft_strlen(cmd) && cmd[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		if (i < (int)ft_strlen(cmd) && cmd[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		i++;
	}
	return (count);
}

char	*cpy_args(char *str)
{
	int		i;
	int		j;
	int		size;
	int		is_open_d;
	int		is_open_s;
	char	*new_str;

	i = 0;
	is_open_d = 0;
	is_open_s = 0;
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	j = i;
	size = 0;
	while (str && j < (int)ft_strlen(str))
	{
		if (str[j] == '"' && is_open_s % 2 == 0)
		{
			j++;
			is_open_d++;
		}
		else if (str[j] == '\'' && is_open_d % 2 == 0)
		{
			j++;
			is_open_s++;
		}
		size++;
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& j < (int)ft_strlen(str) && ft_isspace(str[j]))
			break ;
		j++;
	}
	new_str = malloc(sizeof(char) * ((size) + 1));
	if (!new_str)
		return (NULL);
	j = i;
	i = 0;
	is_open_d = 0;
	is_open_s = 0;
	while (str && j < (int)ft_strlen(str))
	{
		if (str[j] == '"' && is_open_s % 2 == 0)
		{
			j++;
			is_open_d++;
		}
		else if (str[j] == '\'' && is_open_d % 2 == 0)
		{
			j++;
			is_open_s++;
		}
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& j < (int)ft_strlen(str) && ft_isspace(str[j]))
			break ;
		new_str[i++] = str[j];
		j++;
	}
	new_str[i] = 0;
	ft_printf("--%s--\n", new_str);
	return (new_str);
}

char	**get_args(char *cmd)
{
	char	**args;
	int		i;
	int		j;
	int		is_open_d;
	int		is_open_s;
	int		run;

	run = 0;
	while (cmd && cmd[run] && ft_isspace(cmd[run]))
			run++;
	i = count_word(&cmd[run]);
	ft_printf("%d\n", i);
	args = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		is_open_s = 0;
		is_open_d = 0;
		args[j++] = cpy_args(&cmd[run]);
		while (run < (int)ft_strlen(cmd))
		{
			if (cmd[run] == '"' && is_open_s % 2 == 0)
			{
				run++;
				is_open_d++;
			}
			else if (cmd[run] == '\'' && is_open_d % 2 == 0)
			{
				run++;
				is_open_s++;
			}
			if (is_open_d % 2 == 0 && is_open_s % 2 == 0
				&& run < (int)ft_strlen(cmd) && ft_isspace(cmd[run]))
				break ;
			run++;
		}
		run++;
	}
	args[j] = NULL;
	i = 0;
	// while (args[i])
	// 	ft_printf("%s\n", args[i++]);
	return (args);
}
