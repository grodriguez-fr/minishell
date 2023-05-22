/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/22 18:13:19 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

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
	while (cmd && cmd[i])
	{
		if (!isspace(cmd[0]) && i == 0)
			count++;
		while (cmd[i] && isspace(cmd[i]))
		{
			i++;
			if (cmd[i] && !isspace(cmd[i]))
				count ++;
		}
		while (cmd[i] && !isspace(cmd[i]))
			i++;
	}
	return (count);
}

char	*cpy(char *str)
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
	while (str && str[i] && isspace(str[i]))
		i++;
	j = i;
	size = 0;
	while (str && str[j] && j < strlen(str))
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
		j++;
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0 && isspace(str[j]))
			break ;
	}
	new_str = malloc(sizeof(char) * ((size) + 1));
	if (!new_str)
		return (NULL);
	j = i;
	i = 0;
	is_open_d = 0;
	is_open_s = 0;
	while (str && str[j])
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
		new_str[i++] = str[j];
		j++;
		if (is_open_d % 2 == 0 && is_open_s % 2 == 0 && isspace(str[j]))
			break ;
	}
	new_str[i] = 0;
	return (new_str);
}

char **get_args(char *cmd)
{
	char	**args;
	int		i;
	int		j;
	int		is_open_d;
	int		is_open_s;
	int		run;

	i = count_word(cmd);
	args = malloc(sizeof(char *) * (i + 1));
	j = 0;
	run = 0;
	while (j < i)
	{
		is_open_s = 0;
		is_open_d = 0;
		args[j++] = cpy(&cmd[run]);
		while (cmd[run])
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
			if (is_open_d % 2 == 0 && is_open_s % 2 == 0 && isspace(cmd[run]))
				break ;
			run++;
		}
		run++;
	}
	args[j] = NULL;
	return (args);
}

int	main(void)
{
	char	*cmd;
	char	**args;
	int		i;

	i = 0;
	cmd = strdup("e\"c' \"ho la' 'bi\"      \"te");
	args = get_args(cmd);
	while (args[i])
		printf("%s\n", args[i++]);
	return (0);
}
