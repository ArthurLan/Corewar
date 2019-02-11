/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:11:22 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/09 16:33:00 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*list2;

	if (*alst)
	{
		list = *alst;
		while (list)
		{
			list2 = list->next;
			ft_lstdelone(&list, del);
			list = list2;
		}
		*alst = 0;
	}
}
