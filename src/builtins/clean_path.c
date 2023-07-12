/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:16:40 by gurodrig          #+#    #+#             */
/*   Updated: 2023/07/12 16:39:42 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_path_loop(char *path, char *new_path, char **tokens, int i)
{
	char	*last_slash;

	if (ft_strncmp(tokens[i], "..", 2) == 0 && ft_strncmp(tokens[i], "...", 3))
	{
		last_slash = ft_strrchr(new_path, '/');
		if (last_slash)
			*last_slash = 0;
	}
	else if (ft_strncmp(tokens[i], ".", 1) || !ft_strncmp(tokens[i], "...", 3))
	{
		ft_strlcat(new_path, "/", ft_strlen(path) + 1);
		ft_strlcat(new_path, tokens[i], ft_strlen(path) + 1);
	}
}

char	*get_clean_path(char *path)
{
	char	**tokens;
	char	*new_path;
	int		i;

	tokens = ft_split(path, '/');
	if (!tokens)
		return (NULL);
	new_path = (char *)malloc(ft_strlen(path) + 1);
	if (!new_path)
		return (free_split(tokens), NULL);
	new_path[0] = 0;
	i = 0;
	while (tokens[i])
		clean_path_loop(path, new_path, tokens, i++);
	if (!new_path[0])
		ft_strlcpy(new_path, "/", 2);
	return (free_split(tokens), new_path);
}
