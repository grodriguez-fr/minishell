/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:31:07 by astachni          #+#    #+#             */
/*   Updated: 2023/05/26 16:09:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd(t_mini *mini, t_exec *current)
{
	char	*pathname;
	char	**new_env;
	int     ret;

    if (is_builtin(current->cmd_name))
    {
        exit(execute_builtin(mini, current, current->cmd_name));
    }
	new_env = convert_env(mini);
    if (!strchr(current->cmd_name, '/'))
    {
    	pathname = find_path(mini, current->cmd_name);
	    ret = execve(pathname, current->args, new_env);
        free(pathname);
        if (!pathname)
            write_not_found(new_env, current->cmd_name);
    }
    else
    {
	    ret = execve(current->cmd_name, current->args, new_env);
        if (ret == -1)
            perror("Erreur lors de l'execution");
    }
    free_env(new_env);
	exit_errno(ret);
}

int exec_redirection_in(t_exec *current)
{
    int i;
    int fd;

    if (current->is_heredoc && current->here_docs)
    {
        i = 0;
        while (current->here_docs[i + 1])
            i++;
        fd = open(current->here_docs[i], O_RDONLY);
        if (fd == -1)
            return (0);
        dup2(fd, 0);
    }
    else if (current->files_in)
    {
        i = 0;
        while (current->files_in[i + 1])
            i++;
        fd = open(current->files_in[i], O_RDONLY);
        if (fd == -1)
            return (0);
        dup2(fd, 0);
    }
    return (1);
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
	if (!check_redirection(current))
		exit(1);
	if (previous_fd != 0)
	{
		dup2(previous_fd, 0);
		close(previous_fd);
	}
    if (current->next)
	    close(p[0]);
	if (current->next)
		dup2(p[1], 1);
    exec_redirection_in(current);
    exec_redirection_out(current);
    if (current->next)
	    close(p[1]);
	handle_cmd(mini, current);
}

