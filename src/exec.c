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
	int     ret;
    int     is_path;

    if (is_builtin(current->cmd_name))
        exit(execute_builtin(mini, current, current->cmd_name));
    pathname = current->cmd_name;
    if (!strchr(current->cmd_name, '/'))
    {
    	pathname = find_path(mini, current->cmd_name);
        is_path = 1;
    }
	new_env = convert_env(mini);
	ret = execve(pathname, current->args, new_env);
    if (!is_path)
        free(pathname);
    free_env(new_env);
	exit(ret);
}

void    exec_redirection_in(t_exec *current)
{
    int i;
    int fd;

    if (current->is_heredoc && current->here_docs)
    {
        i = 0;
        while (current->here_docs[i + 1])
            i++;
        fd = open(current->here_docs[i], O_RDONLY);
        dup2(fd, 0);
    }
    else if (current->files_in)
    {
        i = 0;
        while (current->files_in[i + 1])
            i++;
        fd = open(current->files_in[i], O_RDONLY);
        dup2(fd, 0);
    }
}

void    exec_redirection_out(t_exec *current)
{
    int i;
    int fd;

    if (current->is_append && current->files_out_a)
    {
        i = 0;
        while (current->files_out_a[i + 1])
            i++;
        fd = open(current->files_out_a[i], O_WRONLY | O_APPEND);
        dup2(fd, 1);
    }
    else if (current->files_out)
    {
        i = 0;
        while (current->files_out[i + 1])
            i++;
        fd = open(current->files_out[i], O_WRONLY);
        dup2(fd, 1);
    }
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
		dup2(p[1], 1); // redirection sortie standard
    exec_redirection_in(current);
    exec_redirection_out(current);
	close(p[1]);
	handle_cmd(mini, current);
}

int	exec_all(t_mini *mini)
{
	t_exec	*current;
	int 	p[2];
	int 	ret;
	int 	previous_fd;

	printf("\n---------exec----------\n");
    heredoc(mini);
	current = mini->ex;
	previous_fd = 0;
    if (builtin_env_modifier(current->cmd_name) && !current->next)
    {
        return (execute_builtin(mini, current, current->cmd_name));
    }
	while (current)
	{
        if (!check_redirection(current))
            return (0);
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
