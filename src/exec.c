/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:07 by astachni          #+#    #+#             */
/*   Updated: 2023/05/15 16:45:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


void	handle_cmd(t_mini *mini, t_exec *current)
{
	char	*pathname;
	char	**new_env;
	int	ret;

	pathname = find_path(mini, current->cmd_name);
	new_env = convert_env(mini);
	ret = execve(pathname, current->args, new_env);
	exit (ret);
}

void	exec_cmd(t_mini *mini, t_exec *current, int p[2], int previous_fd)
{
	if (previous_fd != 0)
	{
		dup2(previous_fd, 0); // redirection entree standard
		close(previous_fd);
	}
	close(p[0]);
	if (current->next)
	{
		dup2(p[1], 1); // redirection sortie standard
	}
	close(p[1]);
	handle_cmd(mini, current);
}

int	exec_all(t_mini *mini)
{
	t_exec	*current;
	int	p[2];
	int	ret;
	int	previous_fd;

	printf("\n---------exec----------\n");
	current = mini->ex;
	previous_fd = 0;
	while (current)
	{
		if (current->next)
			ret = pipe(p);
		if (ret == -1)
			return (0);
		ret = fork();
		if (ret < 0)
			return (0);
		if (ret == 0)
			exec_cmd(mini, current, p, previous_fd);
		if (current->next)
			close(p[1]);
		if (previous_fd != 0)
			close(previous_fd);
		previous_fd = p[0];
		waitpid(ret, 0, 0);
		current = current->next;
	}
	return (1);
}
