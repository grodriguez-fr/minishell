/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:31:11 by astachni          #+#    #+#             */
/*   Updated: 2023/06/01 17:27:41 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env(t_env_p **env, t_mini mini)
{
	char	*pwd;
	int		i;

	pwd = malloc(sizeof(char) * 256);
	if (!pwd)
		exit (1);
	if (getcwd(pwd, 256) != NULL)
	{
		pwd = ft_strf2join("PWD=", pwd);
		if (!pwd)
			error(&mini, "MALLOC ERROR", NULL);
		i = 0;
		while (pwd && pwd[i] && pwd[i] != '=')
			i++;
		add_to_stack(env, i, pwd, mini);
		free(pwd);
		i = 0;
		pwd = ft_strdup("SHLVL=\"1\"");
		if (!pwd)
			error(&mini, "MALLOC ERROR", NULL);
		while (pwd && pwd[i] && pwd[i] != '=')
			i++;
		add_to_stack(env, i, pwd, mini);
		free(pwd);
	}
}

int	increment_shell_level(t_env_p *env)
{
	t_env_p	*current;
	int		current_level;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->key, "SHLVL", 5))
		{
			current_level = ft_atoi(current->value);
			free(current->value);
			current_level++;
			current->value = ft_itoa(current_level);
			if (!current->value)
				return (0);
			return (1);
		}
		current = current->next;
	}
	ft_putstr_fd("minishell: no SHLVL variable\n", 2);
	return (0);
}
