/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:45:00 by astachni          #+#    #+#             */
/*   Updated: 2023/07/12 16:35:25 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(char **envp, t_env_p **env, t_mini mini)
{
	int		i;
	int		j;

	i = 0;
	if (!*envp)
		create_env(env, mini);
	while (envp && envp[i])
	{
		j = 0;
		while (envp && envp[i] && envp[i][j] && envp[i][j] != '=')
			j++;
		add_to_stack(env, j, envp[i], mini);
		i++;
	}
	increment_shell_level(*env);
}

void	add_to_stack(t_env_p **lst, int j, char *value_to_add, t_mini mini)
{
	char	*key;
	char	*value;
	t_env_p	*new_node;

	key = malloc((j + 1) * sizeof(char));
	ft_memcpy(key, value_to_add, j);
	value = ft_strdup(&value_to_add[j + 1]);
	new_node = ft_new(key, value);
	ft_add_back(lst, new_node);
	if (!(*lst) || !(*lst)->key || !(*lst)->value)
		error(&mini, "malloc ERROR\n", NULL);
}

void	ft_add_back(t_env_p **lst, t_env_p *new)
{
	if (!lst)
		return ;
	if (*lst)
		ft_last(*lst)->next = new;
	else
		*lst = new;
}

t_env_p	*ft_new(char *key, char *value)
{
	t_env_p	*elm;

	elm = malloc(sizeof(t_env_p));
	if (!elm)
		return (free(value), free(key), NULL);
	elm->key = key;
	elm->value = value;
	elm->next = NULL;
	return (elm);
}

t_env_p	*ft_last(t_env_p *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
