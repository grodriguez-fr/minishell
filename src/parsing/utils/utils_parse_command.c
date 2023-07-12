/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:59:27 by astachni          #+#    #+#             */
/*   Updated: 2023/07/12 16:35:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_back_cmd(t_exec **lst, t_exec *new);
t_exec	*ft_new_cmd(char *value, char **arg, char *all_pipe);

void	add_cmd(t_exec **lst, char	*cmd_name, char **args, char *all_pipe)
{
	t_exec	*new_node;
	int		i;

	i = 0;
	new_node = ft_new_cmd(cmd_name, args, all_pipe);
	if (!new_node)
	{
		while (args && args[i])
			free(args[i++]);
		if (args)
			free(args);
		return (free(cmd_name), free(all_pipe));
	}
	ft_add_back_cmd(lst, new_node);
}

void	ft_add_back_cmd(t_exec **lst, t_exec *new)
{
	if (!lst)
		return ;
	if (*lst)
		ft_last_cmd(*lst)->next = new;
	else
		*lst = new;
}

t_exec	*ft_new_cmd(char *value, char **arg, char *all_pipe)
{
	t_exec	*elm;

	elm = malloc(sizeof(t_exec));
	elm->cmd_name = value;
	elm->args = arg;
	elm->comp_pipe = all_pipe;
	elm->next = NULL;
	return (elm);
}

t_exec	*ft_last_cmd(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
