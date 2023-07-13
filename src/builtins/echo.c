/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:56:47 by astachni          #+#    #+#             */
/*   Updated: 2023/07/13 13:37:55 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_options(t_exec *ex, size_t *j)
{
	size_t	nb_n;
	int		have_endline;

	*j = 1;
	have_endline = 1;
	while (ex->args && ex->args[*j] && ex->args[*j][0] == '-')
	{
		nb_n = 0;
		while (ex->args[*j][nb_n + 1] == 'n')
			nb_n++;
		if (nb_n + 1 != ft_strlen(ex->args[*j]))
			break ;
		if (nb_n > 0)
			have_endline = 0;
		*j = *j + 1;
	}
	return (have_endline);
}

int	echo(t_exec *ex)
{
	size_t	j;
	int		have_endline;

	if (!ex || !ex->cmd_name || strcmp(ex->cmd_name, "echo") != 0)
		return (1);
	if (write(1, "", 0) == -1)
		return (perror("minishell: cd"), 1);
	have_endline = check_options(ex, &j);
	while (ex->args[j])
	{
		ft_putstr_fd(ex->args[j], 1);
		if (ex->args[j + 1])
			ft_putstr_fd(" ", 1);
		j++;
	}
	if (have_endline)
		ft_putstr_fd("\n", 1);
	return (0);
}
