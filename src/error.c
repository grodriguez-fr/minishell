/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:42:40 by astachni          #+#    #+#             */
/*   Updated: 2023/07/14 15:55:38 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec **exec);

void	error(t_mini *mini, char *message, char **strs)
{
	if (mini->ex)
		free_cmd(&mini->ex, free);
	if (mini->env)
		clear_env(&mini->env, free);
	free_strs(strs);
	ft_putstr_fd(message, 2);
	exit(1);
}

void	free_cmd(t_exec **exec, void (*del)(void*))
{
	t_exec	*next;
	int		i;

	if (!exec || !del)
		return ;
	next = *exec;
	while (next)
	{
		next = next->next;
		i = 0;
		if ((*exec)->args)
		{
			while ((*exec)->args && (*exec)->args[i])
				free((*exec)->args[i++]);
			if ((*exec)->args)
				free((*exec)->args);
		}
		free_exec(exec);
		free((*exec));
		*exec = next;
	}
}

void	free_exec(t_exec **exec)
{
	int	i;

	if ((*exec)->comp_pipe)
		free((*exec)->comp_pipe);
	i = 0;
	while ((*exec)->files_in && (*exec)->files_in[i])
		free((*exec)->files_in[i++]);
	if ((*exec)->files_in)
		free((*exec)->files_in);
	i = 0;
	while ((*exec)->files_out && (*exec)->files_out[i])
		free((*exec)->files_out[i++]);
	if ((*exec)->files_out)
		free((*exec)->files_out);
	i = 0;
	while ((*exec)->here_docs && (*exec)->here_docs[i])
		free((*exec)->here_docs[i++]);
	if ((*exec)->here_docs)
		free((*exec)->here_docs);
	i = 0;
	while ((*exec)->files_out_a && (*exec)->files_out_a[i])
		free((*exec)->files_out_a[i++]);
	if ((*exec)->files_out_a)
		free((*exec)->files_out_a);
}

void	clear_env(t_env_p **env, void (*del)(void*))
{
	t_env_p	*next;

	if (!env || ! del)
		return ;
	next = *env;
	while (next)
	{
		next = next->next;
		if ((*env)->key)
			del((*env)->key);
		if ((*env)->key)
			del((*env)->value);
		free(*env);
		*env = next;
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
		free(strs[i++]);
	if (strs)
		free(strs);
}
