/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/05/13 18:27:57 by astachni         ###   ########.fr       */
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
	return (mini);
}

t_exec	*parse_cmd(char *input, t_exec *exec)
{
	int		i;
	char	**commands;
	char	*cmd_name;

	commands = ft_split_pipe(input, '|');
	i = 0;
	exec = NULL;
	cmd_name = NULL;
	while (commands && commands[i])
	{
		exec = parse_cmd_args(i, commands, cmd_name, exec);
		i++;
	}
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
		add_cmd(&exec, cmd_name, args);
		exec->comp_pipe = comm[i];
	}
	return (exec);
}
