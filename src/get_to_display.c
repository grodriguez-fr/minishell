/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_to_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:07:48 by astachni          #+#    #+#             */
/*   Updated: 2023/07/18 23:51:18 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_command_ret;

void	get_to_display(t_mini *mini)
{
	char	*pwd;
	int		i;

	pwd = get_env_value(mini, "PWD");
	if (!pwd)
	{
		mini->to_display = ft_strdup("A PU PWD >");
		return ;
	}
	i = 0;
	while (pwd && pwd[i])
		i++;
	while (pwd && pwd[i] != '/' && i >= 0)
		i--;
	if (i != 0)
		i++;
	if (g_command_ret == 0)
		mini->to_display = ft_strdup("\033[32m➜  \033[1m\033[35m");
	else
		mini->to_display = ft_strdup("\001\033[31m➜  \033[1m\033[35m");
	mini->to_display = ft_strfjoin(mini->to_display, &pwd[i]);
	mini->to_display = ft_strfjoin(mini->to_display, "\033[33m ✗ \033[0m\002");
}
