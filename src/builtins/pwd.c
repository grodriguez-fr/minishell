/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:06:38 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/13 17:23:44 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_mini *mini)
{
	char	res[256];

	(void) mini;
	getcwd(res, 255);
	if (!res)
		return (1);
	if (ft_printf("%s\n", res) == -1)
		return (1);
	return (0);
}
