/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:49:08 by astachni          #+#    #+#             */
/*   Updated: 2023/06/15 23:03:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_is_display;

void	prompt(t_mini mini)
{
	while (1)
	{
		mini = get_to_display(mini);
		mini.input = readline(mini.to_display);
		if (mini.to_display)
			free(mini.to_display);
		if (!mini.input)
			exit_minishell(&mini, 0);
		else if (*(mini.input) == 0)
			continue ;
		add_history(mini.input);
		mini = parse_and_exec(mini.input, mini);
		if (mini.input)
			free(mini.input);
		exec_all(&mini);
		free_cmd(&mini.ex, free);
	}
}

void	signal_handler(int sign, siginfo_t *info, void	*context)
{
	char	pwd[256];
	char	*to_display;
	t_env_p	*env;
	int		i;

	(void)info;
	env = (t_env_p *)context;
	if (g_is_display == 1 && (sign == SIGINT || sign == SIGQUIT))
	{
		if (getcwd(pwd, 256) != NULL)
		{
			i = 0;
			while (pwd[i])
				i++;
			while (pwd[i] != '/' && i >= 0)
				i--;
			i++;
			to_display = ft_strdup("\033[31m➜  \033[1m\033[35m");
			to_display = ft_strfjoin(to_display, &pwd[i]);
			to_display = ft_strfjoin(to_display, "\033[33m ✗ \033[0m");
			ft_printf("\n%s", to_display, env->value);
			free(to_display);
			ft_bzero(pwd, 256);
		}
	}
    else if (g_is_display == 0 && (sign = SIGINT || sign == SIGQUIT))
        ft_printf("\n");
}
