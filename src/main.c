/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:35 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 16:39:40 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	parse_env(char **envp, t_env_p **env);
void	add_to_stack(t_env_p **lst, int j, char *value_to_add);
void	ft_add_back(t_env_p **lst, t_env_p *new);
t_env_p	*ft_last(t_env_p *lst);
t_env_p	*ft_new(char *key, char *value);

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.env = NULL;
	parse_env(envp, &mini.env);
	while (mini.env)
	{
		ft_printf("%s = ", mini.env->key);
		ft_printf("%s\n", mini.env->value);
		mini.env = mini.env->next;
	}
	return (0);
}

void	parse_env(char **envp, t_env_p **env)
{
	int	i;
	int	j;

	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (envp && envp[i] && envp[i][j] && envp[i][j] != '=')
		{
			j++;
		}
		add_to_stack(env, j, envp[i]);
		i++;
	}
}

void	add_to_stack(t_env_p **lst, int j, char *value_to_add)
{
	char	*key;
	char	*value;
	t_env_p	*new_node;

	key = malloc((j + 1) * sizeof(char));
	ft_memcpy(key, value_to_add, j);
	value = ft_strdup(&value_to_add[j + 1]);
	new_node = ft_new(key, value);
	ft_add_back(lst, new_node);
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
		return (NULL);
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
