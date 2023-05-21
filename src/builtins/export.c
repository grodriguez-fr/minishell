/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:03:20 by astachni          #+#    #+#             */
/*   Updated: 2023/05/21 15:07:39 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	export(t_mini mini, t_exec *ex)
{
	t_env_p	*env;

	if (ft_strncmp(ex->cmd_name, "export", ft_strlen("export")) == 0)
	{
		env = mini.env;
		while (env)
		{
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
			env = env->next;
		}
	}
}
