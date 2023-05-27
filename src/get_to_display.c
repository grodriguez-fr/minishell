/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_to_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:07:48 by astachni          #+#    #+#             */
/*   Updated: 2023/05/21 14:51:35 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_mini	get_to_display(t_mini mini)
{
	t_env_p	*env;
	int		i;

	env = mini.env;
	while (env && ft_strncmp(env->key, "PWD", 3))
		env = env->next;
	i = 0;
	while (env && env->value && env->value[i])
		i++;
	while (env && env->value && env->value[i] != '/' && i >= 0)
		i--;
	i++;
    if (mini.command_return == 0)
	    mini.to_display = ft_strdup("\033[32m➜  \033[1m\033[35m");
    else
	    mini.to_display = ft_strdup("\033[31m➜  \033[1m\033[35m");
	mini.to_display = ft_strfjoin(mini.to_display, &env->value[i]);
	mini.to_display = ft_strfjoin(mini.to_display, "\033[33m ✗ \033[0m");
	return (mini);
}
