/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_NOT_COMPILE.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/15 14:55:57 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

char	*change_cmd(char *str, char sep)
{
	char	*new_str;
	int		i;
	int		is_open;
	int		count;

	i = 0;
	count = 0;
	is_open = 0;
	while (str && i < strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		count++;
		i++;
	}
	new_str = malloc(sizeof(char) * (count + 1));
	i = 0;
	count = 0;
	is_open = 0;
	while (str && i < strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] == ' ')
				i++;
			while (str[i] != ' ')
				i++;
		}
		new_str[count++] = str[i++];
	}
	new_str[count] = 0;
	return (new_str);
}
