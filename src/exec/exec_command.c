/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:52:02 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/19 11:52:35 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_command_ret;

int	exec_all_loop(t_mini *mini, t_exec *ex, int p[2], int *previous_fd)
{
	int	ret;

	ret = 0;
	if (ex->next)
		ret = pipe(p);
	if (ret == -1)
		return (0);
	ret = fork();
	if (ret == -1)
		return (0);
	if (ret == 0)
		exec_cmd(mini, ex, p, *previous_fd);
	ex->pid = ret;
	if (ex->next)
		close(p[1]);
	if (*previous_fd != 0)
		close(*previous_fd);
	*previous_fd = p[0];
	return (ret);
}

void	wait_exec(t_mini *mini)
{
	int		status;
	t_exec	*current;

	current = mini->ex;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
	if (g_command_ret == -1)
	{
		if (WIFEXITED(status))
			g_command_ret = WEXITSTATUS(status);
		else
			g_command_ret = 1;
	}
}

int	exec_all(t_mini *mini)
{
	t_exec	*current;
	int		p[2];
	int		previous_fd;

	current = mini->ex;
	previous_fd = 0;
	g_command_ret = -1;
	if (!heredoc(mini))
		return (ft_putstr_fd("heredoc failed\n", 2), 0);
	if (!current || !current->cmd_name)
		return (g_command_ret = 0, 1);
	if (builtin_env_modifier(current->cmd_name) && !current->next)
	{
		g_command_ret = execute_builtin(mini, current, current->cmd_name);
		return (g_command_ret);
	}
	while (current)
	{
		if (!exec_all_loop(mini, current, p, &previous_fd))
			return (0);
		current = current->next;
	}
	wait_exec(mini);
	return (1);
}
