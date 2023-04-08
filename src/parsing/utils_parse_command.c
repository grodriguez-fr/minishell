/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:59:27 by astachni          #+#    #+#             */
/*   Updated: 2023/04/08 16:02:22 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_add_back_cmd(t_exec **lst, t_exec *new);
t_exec	*ft_new_cmd(char *value, char **arg);
t_exec	*ft_last_cmd(t_exec *lst);

void	add_cmd(t_exec **lst, char	*cmd_name, char **args)
{
	t_exec	*new_node;

	new_node = ft_new_cmd(cmd_name, args);
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

t_exec	*ft_new_cmd(char *value, char **arg)
{
	t_exec	*elm;

	elm = malloc(sizeof(t_exec));
	elm->cmd_name = value;
	elm->args = arg;
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
