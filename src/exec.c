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
	ft_printf("execve (%s, %s, new_env))\n", pathname, current->args[0]);
	ret = execve(pathname, current->args, new_env);
	exit (ret);
}

void	exec_cmd(t_mini *mini, t_exec *current, int p[2], int previous_fd)
{
	printf("---exec cmd child %s\n", current->cmd_name);
	if (previous_fd != 0)
	{
		ft_printf("contenu de previous fd (%d): '%s'\n", previous_fd, get_next_line(previous_fd));
		dup2(previous_fd, 0); // redirection entree standard
		close(previous_fd);
		ft_printf("contenu de previous fd (%d): '%s'\n", previous_fd, get_next_line(previous_fd));
		ft_printf("contenu de 0 (%d): '%s'\n", 0, get_next_line(0));
		ft_printf("entree standard deviens: %d\n", previous_fd);
	}
	if (current->next)
	{
		ft_printf("sortie standard deviens: %d\n", p[1]);
		dup2(p[1], 1); // redirection sortie standard
		close(p[1]);
	}
	else
		close(p[1]);
//	if (current->files_in)
//		dup2(current->files_in, 0); // focntion a faire selon le format de current->in
//	if (current->files_out)
//		dup2(current->files_out, 1); //fonction a faire selon l eformat de current->out
	handle_cmd(mini, current);
	close(p[0]);
	close (p[1]);
}

int	exec_all(t_mini *mini)
{
	t_exec	*current;
	int	p[2];
	int	ret;
	int	previous_fd;

	//if (!heredoc(mini))
	//	return (0);
	// builtins qui bugent avec le bash
	printf("\n---------exec----------\n");
	current = mini->ex;
	previous_fd = 0;
	while (current)
	{
		printf("---- en train de gerer : %s ----\n", current->cmd_name);
		printf("previous fd debut: %d\n", previous_fd);
		if (current->next)
		{
			ret = pipe(p);
			printf("pipe lecture : %d\n", p[0]);
			printf("pipe ecriture : %d\n", p[1]);
		}
		if (ret == -1)
			return (0);
		ret = fork();
		if (ret < 0)
			return (0);
		if (ret == 0)
			exec_cmd(mini, current, p, previous_fd);
		close(p[0]);
		close(p[1]);
		previous_fd = p[0];
		waitpid(ret, 0, 0);
		current = current->next;
	}
	return (1);
}
