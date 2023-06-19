/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:14:32 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/19 13:15:29 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strcmp(char *a, char *b)
{
	int	len;

	len = ft_strlen(a) + ft_strlen(b);
	return (ft_strncmp(a, b, len));
}

t_env_p	*sort_env(t_env_p *env)
{
	t_env_p	*tmp;
	char	*key;
	char	*value;

	tmp = env;
	while (env->next != NULL)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			key = env->key;
			env->key = env->next->key;
			env->next->key = key;
			value = env->value;
			env->value = env->next->value;
			env->next->value = value;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}
