/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurodrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:09:21 by gurodrig          #+#    #+#             */
/*   Updated: 2023/05/16 11:09:23 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int heredoc(t_mini *mini)
{
	unsigned int	i;
	t_exec		*current;
	char		*res;
	int		fd;

	i = 0;
	current = mini->ex;
	while (current)
	{
		if (current->here_docs)
		{
			fd = open_heredoc(i);
			if (fd == -1)
				return (-1);
			res = readline(">");
			while (ft_strncmp(res, current->here_docs, ft_strlen(res)))
				write(fd, res, ft_strlen(res));
			current->here_docs = "heredoc/h" + i;
		}
		current = current->next;
		i++;
	}
	return (0);
}

char    *heredoc_file_name(unsigned int i)
{
    char            *res;
    unsigned int    len;
    unsigned int    nb;

    len = 0;
    while (nb > 0)
    {
        nb /= 10;
        len++;
    }
    res = malloc((sizeof(len) + 5) * char);
    str[len + 4] = 0;
	len--;
    while (i >= 10)
    {
        str[len + 4] = n % 10 + '0';
        i /= 10;
		len--;
    }
    str[len + 4] = i + '0';
	str[0] = 'h';
	str[1] = 'd';
	str[2] = '/';
	str[3] = 'h';
    return (str);
}

int	open_heredoc(unsigned int i)
{
	char	*filename;

	filename = heredoc_file_name(i);
	return (open(filename, O_CREAT | O_WRONLY, 0643));
}