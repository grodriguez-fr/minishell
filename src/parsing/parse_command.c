/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/04/10 15:08:38 by astachni         ###   ########.fr       */
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
		exit_minishell(&mini);
	}
	mini.ex = parse_cmd(input, mini.ex);
	mini.ex->fd_in = STDIN_FILENO;
	mini.ex->fd_out = STDOUT_FILENO;
	return (mini);
}

t_exec	*parse_cmd(char *input, t_exec *exec)
{
	int		i;
	char	**commands;
	char	*cmd_name;

	commands = ft_split(input, '|');
	i = 0;
	exec = NULL;
	while (commands && commands[i])
	{
		exec = parse_cmd_args(i, commands, cmd_name, exec);
		i++;
	}
	i = 0;
	while (commands && commands[i])
		free(commands[i++]);
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
		add_cmd(&exec, cmd_name, args);
	}
	return (exec);
}
