/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:31:11 by astachni          #+#    #+#             */
/*   Updated: 2023/07/12 16:35:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pwd(char *pwd, t_env_p **env, t_mini mini);

void	create_env(t_env_p **env, t_mini mini)
{
	char	*pwd;
	int		i;

	pwd = malloc(sizeof(char) * 256);
	if (!pwd)
		exit (1);
	if (getcwd(pwd, 256) != NULL)
	{
		add_pwd(pwd, env, mini);
		i = 0;
		pwd = ft_strdup("SHLVL=\"1\"");
		if (!pwd)
			error(&mini, "malloc ERROR", NULL);
		while (pwd && pwd[i] && pwd[i] != '=')
			i++;
		add_to_stack(env, i, pwd, mini);
		free(pwd);
	}
}

void	add_pwd(char *pwd, t_env_p **env, t_mini mini)
{
	int	i;

	add_to_stack(env, ft_strlen("OLDPWD ") - 1, "OLDPWD ", mini);
	pwd = ft_strf2join("PWD=", pwd);
	if (!pwd)
		error(&mini, "malloc ERROR", NULL);
	i = 0;
	while (pwd && pwd[i] && pwd[i] != '=')
		i++;
	add_to_stack(env, i, pwd, mini);
	free(pwd);
}

int	increment_shell_level(t_env_p *env)
{
	t_env_p	*current;
	int		current_level;

	current = env;
	while (current)
	{
		if (same_string(current->key, "SHLVL"))
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
