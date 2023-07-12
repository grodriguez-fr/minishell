/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:16:27 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/12 16:39:57 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_ret_export_error(char *var)
{
	ft_putstr_fd("minishell: export: '", 2);
	if (var[0])
		ft_putstr_fd(var, 2);
	else
		ft_putstr_fd("=", 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

char	**export_split(char *input)
{
	char	**result;
	char	*equalptr;
	int		eq_pos;

	equalptr = ft_strchr(input, '=');
	if (!equalptr)
		return (NULL);
	eq_pos = equalptr - input;
	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		return (0);
	result[0] = ft_substr(input, 0, eq_pos);
	result[1] = ft_substr(input, eq_pos + 1, ft_strlen(input) - eq_pos - 1);
	result[2] = NULL;
	return (result);
}
