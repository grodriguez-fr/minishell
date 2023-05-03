/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_in_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:03:19 by astachni          #+#    #+#             */
/*   Updated: 2023/04/26 15:28:30 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_mini	file_out(t_mini mini);
t_mini	file_in(t_mini mini);
t_mini	append(t_mini mini);

t_mini	file_in_out(t_mini mini)
{
	mini = file_out(mini);
	mini = file_in(mini);
	return (mini);
}

t_mini	append(t_mini mini)
{
	t_exec	*exec;
	int		i;

	exec = mini.ex;
	if (exec)
	{
		i = 0;
		while (exec->args && exec->args[i])
		{
			if (ft_strncmp(exec->args[i], ">>",
					ft_strlen(exec->args[i])) == 0)
			{
				if (exec->args[i + 1])
				{
					exec->fd_in = exec->args[i + 1];
					break ;
				}
			}
			i++;
		}
	}
	mini.ex = exec;
	return (mini);
}

t_mini	file_in(t_mini mini)
{
	t_exec	*exec;
	int		i;

	exec = mini.ex;
	if (exec)
	{
		i = 0;
		while (exec->args && exec->args[i])
		{
			if (ft_strncmp(exec->args[i], "<",
					ft_strlen(exec->args[i])) == 0)
			{
				if (exec->args[i + 1])
				{
					exec->fd_in = exec->args[i + 1];
					break ;
				}
			}
			i++;
		}
	}
	mini.ex = exec;
	return (mini);
}


t_mini	file_out(t_mini mini)
{
	t_exec	*exec;
	int		i;

	exec = mini.ex;
	if (exec)
	{
		i = 0;
		while (exec->args && exec->args[i])
		{
			if (ft_strncmp(exec->args[i], ">",
					ft_strlen(exec->args[i])) == 0)
			{
				if (exec->args[i + 1])
				{
					exec->fd_out = exec->args[i + 1];
					break ;
				}
			}
			i++;
		}
	}
	mini.ex = exec;
	return (mini);
}