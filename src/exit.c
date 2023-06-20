/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:58:57 by astachni          #+#    #+#             */
/*   Updated: 2023/06/13 22:47:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_mini *mini, int code)
{
	if (mini->env)
		clear_env(&mini->env, free);
	clean_heredocs();
	rl_clear_history();
	free_cmd(&mini->ex, free);
	exit(code);
}

void    exit_minishell_nohd(t_mini *mini, int code)
{
	if (mini->env)
		clear_env(&mini->env, free);
	rl_clear_history();
	free_cmd(&mini->ex, free);
	exit(code);
}

int	clean_heredocs(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

	dir = opendir("/tmp");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (!strncmp(entry->d_name, ".heredoc_tmp_file", 17))
		{
			path = ft_strjoin("/tmp/", entry->d_name);
			if (!path)
				return (0);
			if (unlink(path))
				perror("minishell: file suppression");
			free(path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}
