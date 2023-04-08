/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:24:16 by astachni          #+#    #+#             */
/*   Updated: 2023/04/08 14:32:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		skip_alloc(char *input, t_exec **exec);
void	fill_tab(char *input, t_exec **exec, int i);

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
}

void	parse_cmd(char *input, t_exec **exec)
{
	int		i;
	int		save_i;
	int		arg_number;
	int		cmd_size;

	i += skip_alloc(input, exec);
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
	fill_tab(input, exec, i);
}

int	skip_alloc(char *input, t_exec **exec)
{
	int	i;
	int	cmd_size;

	i = 0;
	(*exec)->cmd_name = NULL;
	while (input && input[i] && input[i] == ' ')
		i++;
	cmd_size = 0;
	while (input && input[i + cmd_size] && input[i + cmd_size] != ' ')
		cmd_size++;
	(*exec)->cmd_name = malloc(sizeof(char) * (cmd_size + 1));
	ft_memcpy((*exec)->cmd_name, &input[i], cmd_size);
	return (i + cmd_size);
}

void	fill_tab(char *input, t_exec **exec, int i)
{
	int	arg_number;
	int	save_i;
	int	cmd_size;

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
			i++;
		arg_number++;
	}
	(*exec)->args[arg_number] = NULL;
}
