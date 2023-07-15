/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:19:49 by astachni          #+#    #+#             */
/*   Updated: 2023/07/15 12:15:54 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_heredoc(int sign)
{
	printf("test");
	if (sign == SIGQUIT)
		return ;
}

char	*heredoc_file_name(unsigned int nb)
{
	char	*res;
	char	*res2;

	res = ft_itoa(nb);
	if (!res)
		return (0);
	res2 = ft_strjoin("/tmp/.heredoc_tmp_file", res);
	if (!res2)
		return (free(res), NULL);
	return (free(res), res2);
}

int	open_heredoc(unsigned int i)
{
	char	*filename;
	int		fd;

	filename = heredoc_file_name(i);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (free(filename), fd);
}
