/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <astachni>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:26:01 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/11/20 01:05:27 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	next = *lst;
	while (next != NULL)
	{
		next = next->next;
		del((*lst)->content);
		free(*lst);
		*lst = next;
	}
}
