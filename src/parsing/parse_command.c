/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/05/26 16:36:11 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*parse_cmd_args(int i, char **comm, char *cmd_name, t_exec *exec);

t_mini	parse_and_exec(char *input, t_mini mini)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		if (input)
			free(input);
		exit_minishell(&mini, 0);
	}
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
			error(&mini, "MALLOC ERROR\n", commands);
		exec = parse_cmd_args(i, commands, NULL, exec);
		ft_last_cmd(exec)->files_out = ex->files_out;
		ft_last_cmd(exec)->files_in = ex->files_in;
		ft_last_cmd(exec)->here_docs = ex->here_docs;
		ft_last_cmd(exec)->files_out_a = ex->files_out_a;
		ft_last_cmd(exec)->is_append = ex->is_append;
		ft_last_cmd(exec)->is_heredoc = ex->is_heredoc;
		free(commands[i]);
		free(ex);
	}
	free(commands);
	return (exec);
}

t_exec	*parse_cmd_args(int i, char **comm, char *cmd_name, t_exec *exec)
{
	char	**args;

	args = get_args(comm[i]);
	if (args && args[0])
		cmd_name = args[0];
	if (args && cmd_name)
		add_cmd(&exec, cmd_name, args, ft_strdup(comm[i]));
	else
		add_cmd(&exec, NULL, NULL, NULL);
	return (exec);
}
