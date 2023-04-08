/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/04/08 16:30:50 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*parse_cmd_args(int i, char **commands, char *cmd_name, t_exec *exec);

void	parse_and_exec(char *input, t_mini mini)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		if (input)
			free(input);
		exit_minishell(&mini);
	}
	mini.ex = parse_cmd(input, mini.ex);
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
}

t_exec	*parse_cmd_args(int i, char **commands, char *cmd_name, t_exec *exec)
{
	int		j;
	int		save_j;
	char	**args;

	j = 0;
	while (commands && commands[i] && commands[i][j])
	{
		while (commands[i] && commands[i][j] && commands[i][j] == ' ')
			j++;
		save_j = j;
		while (commands[i] && commands[i][j + save_j] &&
			commands[i][j + save_j] != ' ')
			save_j++;
		cmd_name = ft_calloc(sizeof(char), save_j + 1);
		ft_memcpy(cmd_name, &commands[i][j], save_j);
		j += save_j;
		while (commands[i] && commands[i][j] && commands[i][j] == ' ')
			j++;
		args = ft_split(&commands[i][j], ' ');
		while (commands[i][j])
			j++;
		add_cmd(&exec, cmd_name, args);
	}
	return (exec);
}
