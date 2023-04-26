/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/04/26 16:53:52 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_exec	*parse_cmd_args(int i, char **comm, char *cmd_name, t_exec *exec);
int		verify_input(char *str);
int		double_quote_error(char	*str);

t_mini	parse_and_exec(char *input, t_mini mini)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		if (input)
			free(input);
		exit_minishell(&mini);
	}
	if (verify_input(input) == 0)
		mini.ex = parse_cmd(input, mini.ex);
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
	cmd_name = NULL;
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

int	verify_input(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	while (str && str[i])
	{
		quote_count = 0;
		while (str && str[i] && str[i] != '|')
		{
			if (str[i] == '\'')
				quote_count++;
			i++;
		}
		if (quote_count % 2 != 0)
		{
			ft_printf("quote error\n");
			return (1);
		}
		i++;
	}
	if (double_quote_error(str) == 1)
		return (1);
	return (0);
}

int	double_quote_error(char	*str)
{
	int	i;
	int	quote_count;

	i = 0;
	while (str && str[i])
	{
		quote_count = 0;
		while (str && str[i] && str[i] != '|')
		{
			if (str[i] == '\"')
				quote_count++;
			i++;
		}
		if (quote_count % 2 != 0)
		{
			ft_printf("quote error\n");
			return (1);
		}
		i++;
	}
}