/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/05/24 16:42:05 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*parse_cmd_args(int i, char **comm, char *cmd_name, t_exec *exec);
size_t	count_sep(char *str, char sep);
char	*change_cmdf(char *str, char sep);

t_mini	parse_and_exec(char *input, t_mini mini)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		if (input)
			free(input);
		exit_minishell(&mini);
	}
	mini.ex = parse_cmd(input, mini.ex, mini);
	return (mini);
}

t_exec	*parse_cmd(char *input, t_exec *exec, t_mini mini)
{
	int		i;
	char	**commands;
	char	*cmd_name;
	char	**files_out;
	char	**files_in;
	char	**heardoc = NULL;
	char	**append = NULL;

	commands = ft_split_pipe(input, '|');
	i = 0;
	exec = NULL;
	cmd_name = NULL;
	while (commands && commands[i])
	{
		heardoc = hear_append(heardoc, commands[i], "<<");
		append = hear_append(append, commands[i], ">>");
		commands[i] = change_cmdf_here_append(commands[i], ">>");
		commands[i] = change_cmdf_here_append(commands[i], "<<");
		files_out = in_out(files_out, commands[i], '>');
		files_in = in_out(files_in, commands[i], '<');
		commands[i] = change_cmdf(commands[i], '>');
		commands[i] = change_cmdf(commands[i], '<');
		if (!commands[i])
			error(&mini, "MALLOC ERROR\n", commands);
		exec = parse_cmd_args(i, commands, cmd_name, exec);
		ft_last_cmd(exec)->files_out = files_out;
		ft_last_cmd(exec)->files_in = files_in;
		ft_last_cmd(exec)->here_docs = heardoc;
		ft_last_cmd(exec)->files_out_a = append;
		free(commands[i]);
		i++;
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

char	*change_cmdf(char *str, char sep)
{
	char	*new_str;
	size_t	i;
	size_t	is_open;
	size_t	count;

	count = count_sep(str, sep);
	new_str = malloc(sizeof(char) * (count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	count = 0;
	is_open = 0;
	while (str && i < ft_strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		new_str[count++] = str[i++];
	}
	new_str[count] = 0;
	free(str);
	return (new_str);
}

size_t	count_sep(char *str, char sep)
{
	size_t	is_open;
	size_t	i;
	size_t	count;

	is_open = 0;
	i = 0;
	count = 0;
	while (str && i < ft_strlen(str))
	{
		if (str[i] == '"')
			is_open++;
		if (str[i] == sep && is_open % 2 == 0)
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		count++;
		i++;
	}
	return (count);
}
