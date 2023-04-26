/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:56:47 by astachni          #+#    #+#             */
/*   Updated: 2023/04/26 15:08:24 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	echo(t_exec *ex, char *str, int fd)
{
	size_t	i;
	size_t	nb_n;
	size_t	j;

	if (!ex || strcmp(ex->cmd_name, "echo") != 0)
		return ;
	j = 0;
	while (ex->args && ex->args[j] && ex->args[j][0] == '-')
	{
		nb_n = 1;
		while (ex->args[j][nb_n] == 'n')
			nb_n++;
		if (nb_n != ft_strlen(ex->args[j]))
			break ;
		j++;
	}
	i = j;
	ft_putstr_fd(str, fd);
	if (j == 0)
		ft_putstr_fd("\n", fd);
}
