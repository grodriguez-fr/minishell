/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:03:20 by astachni          #+#    #+#             */
/*   Updated: 2023/05/21 15:07:39 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_to_env(t_mini *mini, char *key, char *value)
{
	t_env_p	*current;
	t_env_p	*new_var;

    current = mini->env;
    while (current->next)
        current = current->next;

    new_var = malloc(sizeof(t_env_p));
    if (!new_var)
        return (0);
    current->next = new_var;
    new_var->next = NULL;
    new_var->key = ft_strdup(key);
    if (!new_var->key)
        return (0);
    if (value)
        new_var->value = ft_strdup(value);
    if (!new_var->value)
        return (0);
    if (!value)
        new_var->value = NULL;
    return (1);
}

int replace_or_add(t_mini *mini, char *var)
{
	t_env_p	*current;
    char    **splited;
    int     ret;
    
    current = mini->env;
    splited = ft_split(var, '=');
    if (!splited)
        return (0);
    while (current)
    {
        if (!ft_strncmp(current->key, splited[0], \
            ft_strlen(current->key) + ft_strlen(splited[0])))
        {
            free(current->value);
            current->value = ft_strdup(splited[1]);
            return (free_split(splited), 1);
        }
        current = current->next;
    }
    ret = add_to_env(mini, splited[0], splited[1]);
    return (free_split(splited), ret);
}

int replace_or_add_if_valid(t_mini *mini, char *var)
{
    if (is_str_numeric(var))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '?'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '*'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '@'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '$'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '!'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    if (strchr(var, '_'))
        return (ft_putstr_fd("minishell: export: invalid identifier\n", 2), 0);
    return (replace_or_add(mini, var));
}

int	export(t_mini *mini, t_exec *ex)
{
	t_env_p	*current;
    int     i;

	if (ex->args[1] == NULL)
	{
		current = mini->env;
		while (current)
		{
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		    current = current->next;
		}
	}
    i = 1;
    while (ex->args[i])
        if (!replace_or_add_if_valid(mini, ex->args[i++]))
            return (1);
    return (0);
}
