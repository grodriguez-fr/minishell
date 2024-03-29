/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/07/14 16:16:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*parse_cmd_args(char *comm, char *cmd_name, t_exec *exec, t_mini *mini);
t_exec	*add_file(t_exec *exec, t_exec *ex);

t_mini	parse_and_exec(char *input, t_mini mini)
{
	mini.ex = parse_cmd(input, mini.ex, mini);
	return (mini);
}

static char	*get_command(char *cmd, t_exec *ex)
{
	int	redirect;

	redirect = take_last_redirect(cmd);
	ex->here_docs = hear_append(ex->here_docs, cmd, "<<");
	ex->files_out_a = hear_append(ex->files_out_a, cmd, ">>");
	cmd = change_cmdf_here_append(cmd, ">>");
	cmd = change_cmdf_here_append(cmd, "<<");
	ex->files_out = in_out(ex->files_out, cmd, '>');
	ex->files_in = in_out(ex->files_in, cmd, '<');
	cmd = change_cmdf(cmd, '>');
	cmd = change_cmdf(cmd, '<');
	ex->is_append = 0;
	ex->is_heredoc = 0;
	if (redirect == 1)
		ex->is_append = 1;
	else if (redirect == 2)
		ex->is_heredoc = 1;
	return (cmd);
}

t_exec	*parse_cmd(char *input, t_exec *exec, t_mini mini)
{
	int		i;
	char	**commands;
	t_exec	*ex;

	commands = ft_split_pipe(input, '|');
	i = -1;
	while (commands && commands[++i])
	{
		ex = malloc(sizeof(t_exec));
		commands[i] = get_command(commands[i], ex);
		if (!commands[i])
			commands[i] = NULL;
		exec = parse_cmd_args(commands[i], NULL, exec, &mini);
		if (!exec)
		{
			free_cmd(&ex, free);
			error(&mini, "malloc ERROR\n", commands);
		}
		exec = add_file(exec, ex);
		free(commands[i]);
		free(ex);
	}
	free(commands);
	return (exec);
}

t_exec	*add_file(t_exec *exec, t_exec *ex)
{
	ft_last_cmd(exec)->files_out = ex->files_out;
	ft_last_cmd(exec)->files_in = ex->files_in;
	ft_last_cmd(exec)->here_docs = ex->here_docs;
	ft_last_cmd(exec)->files_out_a = ex->files_out_a;
	ft_last_cmd(exec)->is_append = ex->is_append;
	ft_last_cmd(exec)->is_heredoc = ex->is_heredoc;
	return (exec);
}

t_exec	*parse_cmd_args(char *comm, char *cmd_name, t_exec *exec, t_mini *mini)
{
	char	**args;

	(void) cmd_name;
	args = get_args(comm);
	args = take_var(mini, comm, args);
	if (!args)
		args = NULL;
	if (args && args[0])
		cmd_name = args[0];
	if (args && cmd_name)
		add_cmd(&exec, cmd_name, args, ft_strdup(comm));
	else
		add_cmd(&exec, NULL, NULL, NULL);
	return (exec);
}
