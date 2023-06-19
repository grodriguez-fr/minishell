/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:42:09 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/19 11:42:19 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	write_not_found(t_mini *mini, char **new_env, char *name)
{
	char	*to_write;
	char	*buffer;

	free_env(new_env);
	buffer = ft_strjoin("minishell: ", name);
	to_write = ft_strjoin(buffer, ": command not found\n");
	free(buffer);
	ft_putstr_fd(to_write, 2);
	free(to_write);
	exit_minishell(mini, 127);
}

void	exit_errno(t_mini *mini, int ret)
{
	if (ret == -1 && errno == 22)
		exit_minishell(mini, 127);
	if (ret == -1 && errno == 13)
		exit_minishell(mini, 126);
	exit_minishell(mini, ret);
}
