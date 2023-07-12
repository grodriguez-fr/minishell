/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:41:09 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/12 21:18:02 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	same_string(char *a, char *b)
{
	if (a && b)
		return (!ft_memcmp(a, b, ft_strlen(a)) && ft_strlen(a) == ft_strlen(b));
	else
		return (1);
}

int	is_builtin(char *cmd_name)
{
	if (same_string(cmd_name, "echo"))
		return (1);
	if (same_string(cmd_name, "cd"))
		return (1);
	if (same_string(cmd_name, "pwd"))
		return (1);
	if (same_string(cmd_name, "export"))
		return (1);
	if (same_string(cmd_name, "unset"))
		return (1);
	if (same_string(cmd_name, "env"))
		return (1);
	if (same_string(cmd_name, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_mini *mini, t_exec *ex, char *cmd_name)
{
	if (same_string(cmd_name, "echo"))
		return (echo(ex));
	if (same_string(cmd_name, "cd"))
		return (cd(mini, ex));
	if (same_string(cmd_name, "pwd"))
		return (pwd(mini));
	if (same_string(cmd_name, "export"))
		return (export(mini, ex));
	if (same_string(cmd_name, "unset"))
		return (unset(mini, ex));
	if (same_string(cmd_name, "env"))
		return (env(mini));
	if (same_string(cmd_name, "exit"))
		return (exit_builtin(mini, ex));
	ft_printf("builtin inconnue??\n");
	return (0);
}

int	builtin_env_modifier(char *cmd_name)
{
	if (same_string(cmd_name, "cd"))
		return (1);
	if (same_string(cmd_name, "export"))
		return (1);
	if (same_string(cmd_name, "unset"))
		return (1);
	if (same_string(cmd_name, "exit"))
		return (1);
	return (0);
}
