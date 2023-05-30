/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:31:11 by astachni          #+#    #+#             */
/*   Updated: 2023/04/26 17:31:41 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env(void)
{
	char	*pwd;
	char	*path;

	pwd = malloc(sizeof(char) * 255);
	pwd = getcwd(pwd, 256);
	ft_printf("%s, %d", pwd, ft_strlen(pwd));
	path = ft_strdup \
	("/home/zorkz/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin\
:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	ft_printf("%s", path);
	exit(0);
}

int    increment_shell_level(t_env_p *env)
{
    t_env_p *current;
    int     current_level;

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
