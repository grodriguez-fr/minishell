/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:07 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 20:43:41 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// il faut utiliser execve

int exec_all(t_mini *mini)
{
	t_exec	*current;
	int	p[2];
	int	ret;
	int	previous_fd;

	if (!heredoc(mini))
		return (0);
	// builtins qui bugent avec le bash
	current = mini->exec;
	previous_fd = 0;
	while (current)
	{
		p = pipe();
		if (p == -1)
			return (0);
		ret = fork();
		if (ret < 0)
			return (0);
		if (ret == 0)
			exec_cmd(mini, current, p);
		close (p[0]);
		if (previous_fd)
			close (previous_fd);
		previous_fd = p[1];
		waitpid(ret, 0, 0);
		current = current->next;
	}
	close(previous_fd);
	return (1);
}

void	exec_cmd(t_mini *mini, t_exec *current, int p[2])
{
	if (current->next)
		dup2(p[1], 1); // redirection sortie standard
	if (current->previous)
		dup2(previous_fd, 0); // redirection entree standard
	if (current->in)
		dup2(current->in, 0); // focntion a faire selon le format de current->in
	if (current->out)
		dup2(current->out, 1); //fonction a faire selon l eformat de current->out
	handle_cmd(mini, current);
	close (p[0]);
	close (p[1]);
}

void	handle_cmd(t_mini *mini, t_exec *current)
{
	char	*pathname;
	char	**new_env;

	// manipulations ou pas sur le pathname
	new_env = convert_env(mini->env);
	execve(pathname, current->args, new_env);
}

int	heredoc(t_mini *mini)
{
	unsigned int	i;
	t_exec		*current;
	char		*res;
	int		fd;

	i = 1;
	current = mini->exec;
	while (current)
	{
		if (heredoc)
		{
			fd = open("heredoc/h" + i, O_CREAT | O_WRONLY, 0644);
			if (fd == -1)
				return (0);
			res = readline(">");
			while (strstr(res, current->heredoc))
				write(fd, res, ft_strlen(res));
			current->heredoc = "heredoc/h" + i;
		}
		current = current->next;
		i++;
	}
	return (1);
}
