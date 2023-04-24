/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:56:47 by astachni          #+#    #+#             */
/*   Updated: 2023/04/24 18:03:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	echo(t_mini mini)
{
	t_exec	*temp;
	size_t	i;
	size_t	nb_n;
	size_t	j;

	temp = mini.ex;
	if (!mini.ex || strcmp(temp->cmd_name, "echo") != 0)
		return ;
	j = 0;
	while (temp->args && temp->args[j] && temp->args[j][0] == '-')
	{
		nb_n = 1;
		while (temp->args[j][nb_n] == 'n')
			nb_n++;
		if (nb_n != ft_strlen(temp->args[j]))
			break ;
		j++;
	}
	i = j;
	while (temp->args && temp->args[i])
	{
		ft_printf("%s", temp->args[i++]);
		if (temp->args[i])
			ft_printf(" ");
	}
	if (j == 0)
		ft_printf("\n");
}
