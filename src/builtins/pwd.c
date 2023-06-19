/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:06:38 by gurodrig          #+#    #+#             */
/*   Updated: 2023/06/19 13:06:40 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	pwd(t_mini *mini)
{
	char	*res;

	res = get_env_value(mini, "PWD");
	if (!res)
		return (1);
	if (ft_printf("%s\n", res) == -1)
		return (1);
	return (0);
}
