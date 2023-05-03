/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:10 by astachni          #+#    #+#             */
/*   Updated: 2023/05/03 17:51:59 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_isspace(char c)
{
	if ((c >= 7 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	*count_nb(char *str)
{
	int	*index_return;
	int	is_open;

	index_return = (int *)malloc(sizeof(int) * 2);
	index_return[0] = 0;
	index_return[1] = 0;
	is_open = 0;
	while (str && str[index_return[0]] && ft_isspace(str[index_return[0]]))
		index_return[0]++;
	while (str && str[index_return[0]])
	{
		if (str[index_return[0]] == '"')
		{
			while (str[index_return[0]] && str[index_return[0]] == '"')
			{
				is_open++;
				index_return[0]++;
			}
		}
		else if (str[index_return[0]] == '|' && is_open % 2 == 0)
			break ;
		if (ft_isspace(str[index_return[0]]) && is_open % 2 == 0)
			break ;
		index_return[0]++;
		index_return[1]++;
	}
	return (index_return);
}

void	cpy_char(char *src, char *dest)
{
	int	i;
	int	j;
	int	is_open;

	i = 0;
	j = 0;
	is_open = 0;
	while (src && src[i] && ft_isspace(src[i]))
		i++;
	while (src && src[i])
	{
		if (src[i] == '"')
		{
			while (src[i] && src[i] == '"')
			{
				is_open++;
				i++;
			}
		}
		else if (src[i] == '|' && is_open % 2 == 0)
			break ;
		if (ft_isspace(src[i]) && is_open % 2 == 0)
			break ;
		dest[j++] = src[i++];
	}
	dest[j] = 0;
}

char	**ft_split_the_cock(char *str, char sep)
{
	int		i;
	int		count;
	int		is_open;
	char	**to_return;

	i = 0;
	is_open = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ' && is_open % 2 == 0)
			i++;
		if (str[i] == '"')
		{
			while (str[i] && str[i] == '"')
			{
				is_open++;
				i++;
			}
		}
		else if (str[i] == sep && is_open % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] == sep)
				return (NULL);
			count ++;
		}
		i++;
	}
	if (count > 0)
		count ++;
	printf("---%d---\n", count);
	to_return = malloc(sizeof(char *) + (count + 1));
	return(to_return);
}

int	main(void)
{
	char	*str = "\"ec\"\"ho\" bonjour | abcde";
	char	*cmd;
	char	*arg;
	int		*count;
	char	*temp;

	// count = count_nb(str);
	// cmd = malloc(sizeof(char) * (count[1] + 1));
	// cpy_char(str, cmd);
	// temp = &str[count[0]];
	// free(count);
	// count = count_nb(temp);
	// arg = malloc(sizeof(char) * (count[1] + 1));
	// cpy_char(temp, arg);
	// printf("|%s, %s|\n", cmd, arg);
	// free(cmd);
	// free(arg);
	// free(count);
	ft_split_the_cock(str, '|');
	return (0);
}
