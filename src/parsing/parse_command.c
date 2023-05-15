/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/05/15 17:50:16 by astachni         ###   ########.fr       */
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

	commands = ft_split_pipe(input, '|');
	i = 0;
	exec = NULL;
	cmd_name = NULL;
	while (commands && commands[i])
	{
		files_out = in_out(files_out, commands[i], '>');
		files_in = in_out(files_in, commands[i], '<');
		commands[i] = change_cmdf(commands[i], '>');
		commands[i] = change_cmdf(commands[i], '<');
		if (!commands[i])
			error(&mini, "MALLOC ERROR\n", commands);
		exec = parse_cmd_args(i, commands, cmd_name, exec);
		ft_last_cmd(exec)->files_out = files_out;
		ft_last_cmd(exec)->files_in = files_in;
		free(commands[i]);
		i++;
	}
	free(commands);
	return (exec);
}

t_exec	*parse_cmd_args(int i, char **comm, char *cmd_name, t_exec *exec)
{
	int		j;
	int		save_j;
	char	**args;

	j = 0;
	while (comm && comm[i] && comm[i][j])
	{
		j = 0;
		cmd_name = NULL;
		while (comm[i] && comm[i][j] && comm[i][j] == ' ')
			j++;
		save_j = j;
		while (comm[i] && comm[i][j + save_j] && comm[i][j + save_j] != ' ')
			save_j++;
		cmd_name = malloc(sizeof(char) * (save_j + 1));
		ft_memcpy(cmd_name, &comm[i][j], save_j);
		j += save_j;
		while (comm[i] && comm[i][j] && comm[i][j] == ' ')
			j++;
		args = ft_split(&comm[i][j], ' ');
		while (comm[i][j])
			j++;
		add_cmd(&exec, cmd_name, args, ft_strdup(comm[i]));
	}
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
