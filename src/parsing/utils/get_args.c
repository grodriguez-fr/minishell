/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:34:38 by astachni          #+#    #+#             */
/*   Updated: 2023/06/21 14:04:02 by astachni         ###   ########.fr       */
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
		if (cmd[i] && ft_isspace(cmd[i]) == 1 && ft_isspace(cmd[i + 1]) == 0
			&& cmd[i + 1] && is_open_d % 2 == 0 && is_open_s % 2 == 0)
			count ++;
		if (i < (int)ft_strlen(cmd) && cmd[i] == '"' && is_open_s % 2 == 0)
			is_open_d++;
		if (i < (int)ft_strlen(cmd) && cmd[i] == '\'' && is_open_d % 2 == 0)
			is_open_s++;
		i++;
	}
	return (count);
}

int	find_next_argument_index(char *cmd, int current_index)
{
	size_t	is_open_s;
	size_t	is_open_d;
	size_t	run;

	is_open_s = 0;
	is_open_d = 0;
	run = current_index;
	while (run < ft_strlen(cmd))
	{
		is_open_s = is_open(cmd, run, is_open_d, '\'');
		is_open_d = is_open(cmd, run, is_open_s, '"');
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0 && cmd[run + 1] && \
			cmd[run + 1] != ' ' && run < ft_strlen(cmd) && ft_isspace(cmd[run]))
			break ;
		run++;
	}
	run++;
	return (run);
}

char	**get_args(char *cmd)
{
	char	**args;
	int		i;
	int		j;
	int		run;

	run = 0;
	while (cmd && cmd[run] && ft_isspace(cmd[run]))
		run++;
	i = count_word(&cmd[run]);
	args = NULL;
	if (i > 0)
		args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	j = 0;
	while (j < i)
	{
		args[j] = cpy_args(&cmd[run]);
		if (!args[j])
			return (free_strs(args), NULL);
		j++;
		run = find_next_argument_index(cmd, run);
	}
	args[j] = NULL;
	return (args);
}

int	get_argument_size(char *str, int start_index)
{
	size_t	j;
	size_t	size;
	size_t	is_open_d;
	size_t	is_open_s;

	j = start_index;
	size = 0;
	is_open_d = 0;
	is_open_s = 0;
	while (str && j < ft_strlen(str))
	{
		is_open_d += is_open(str, j, is_open_s, '"');
		is_open_s += is_open(str, j, is_open_d, '\'');
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0
			&& j < ft_strlen(str) && ft_isspace(str[j]))
			break ;
		if (str[j] != '\'' && str[j] != '"')
			size++;
		j++;
	}
	return (size);
}
