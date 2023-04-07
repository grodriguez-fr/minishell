/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 20:20:48 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_and_exec(char *input, t_mini mini)
{
	if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
	{
		if (input)
			free(input);
		exit_minishell(&mini);
	}
	(&mini)->ex = malloc(sizeof(t_exec));
	parse_cmd(input, &mini.ex);
	int i = 0;
	while (mini.ex->args[i])
	{
		ft_printf("%s\n", mini.ex->args[i++]);
	}
}

void	parse_cmd(char *input, t_exec **exec)
{
	int		i;
	int		save_i;
	int		arg_number;
	int		cmd_size;
	char	*cmd;

	i = 0;
	cmd = NULL;
	while (input && input[i] && input[i] == ' ')
		i++;
	cmd_size = 0;
	while (input && input[i + cmd_size] && input[i + cmd_size] != ' ')
		cmd_size++;
	cmd = malloc(sizeof(char) * (cmd_size + 1));
	ft_memcpy(cmd, &input[i], cmd_size);
	i += cmd_size;
	arg_number = 0;
	save_i = i;
	while (input && input[i] && (input[i] != '|'
			|| ft_memcmp(&input[i], ">>", 2) == 0))
	{
		if (input[i] && input[i] == ' ')
		{
			arg_number++;
			while (input[i] && input[i] == ' ')
				i++;
			i--;
		}
		i++;
	}
	i = save_i;
	(*exec)->args = malloc(sizeof(char *) * (arg_number + 1));
	arg_number = 0;
	while (input && input[i] && (input[i] != '|'
			|| ft_memcmp(&input[i], ">>", 2) == 0))
	{
		cmd_size = 0;
		while (input[i] && input[i] == ' ')
			i++;
		save_i = i;
		while (input[i] && input[i] != ' ')
		{
			i++;
			cmd_size++;
		}
		(*exec)->args[arg_number] = malloc(sizeof(char) * (cmd_size + 1));
		i = save_i;
		ft_memcpy((*exec)->args[arg_number], &input[i], cmd_size);
		while (input[i] && input[i] != ' ')
		{
			i++;
		}
		arg_number++;
	}
	(*exec)->args[arg_number] = NULL;
}
