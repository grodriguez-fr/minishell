/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:03:20 by astachni          #+#    #+#             */
/*   Updated: 2023/07/13 15:43:59 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_env(t_mini *mini, char *key, char *value)
{
	t_env_p	*current;
	t_env_p	*new_var;

	current = mini->env;
	while (current && current->next)
		current = current->next;
	new_var = malloc(sizeof(t_env_p));
	if (!new_var)
		return (0);
	if (current)
		current->next = new_var;
	else
		mini->env = new_var;
	new_var->next = NULL;
	new_var->key = ft_strdup(key);
	if (!new_var->key)
		return (0);
	if (value)
		new_var->value = ft_strdup(value);
	if (!new_var->value && value)
		return (0);
	if (!value)
		new_var->value = NULL;
	return (1);
}

int	is_valid_id(char *var)
{
	if (is_str_numeric(var))
		return (write_ret_export_error(var));
	if (ft_strchr(var, '?') || ft_strchr(var, '*') || ft_strchr(var, '@'))
		return (write_ret_export_error(var));
	if (ft_strchr(var, '$') || ft_strchr(var, '!') || ft_strchr(var, '%'))
		return (write_ret_export_error(var));
	if (ft_strchr(var, '_') || ft_strchr(var, '.') || ft_strchr(var, '%'))
		return (write_ret_export_error(var));
	if (ft_strchr(var, '#') || ft_strchr(var, '{') || ft_strchr(var, '}'))
		return (write_ret_export_error(var));
	if (ft_strchr(var, '+') || ft_strchr(var, '{') || ft_strchr(var, '}'))
		return (write_ret_export_error(var));
	return (1);
}

int	replace_or_add(t_mini *mini, char *var)
{
	t_env_p	*current;
	char	**splited;
	int		ret;

	current = mini->env;
	splited = export_split(var);
	if (!splited || !is_valid_id(splited[0]))
		return (free_split(splited), 0);
	while (current)
	{
		if (same_string(current->key, splited[0]))
		{
			free(current->value);
			if (splited[1])
				current->value = ft_strdup(splited[1]);
			else
				current->value = NULL;
			return (free_split(splited), 1);
		}
		current = current->next;
	}
	ret = add_to_env(mini, splited[0], splited[1]);
	return (free_split(splited), ret);
}

int	export(t_mini *mini, t_exec *ex)
{
	t_env_p	*current;
	int		i;

	if (ex->args[1] == NULL)
	{
		current = sort_env(mini->env);
		while (current)
		{
			if (current->value)
				ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
			else
				ft_printf("declare -x %s\n", current->key);
			current = current->next;
		}
	}
	i = 1;
	while (ex->args[i])
		if (!replace_or_add(mini, ex->args[i++]))
			return (1);
	return (0);
}
