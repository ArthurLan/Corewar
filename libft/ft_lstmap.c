/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:41:45 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/10 14:20:50 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;
	t_list	*first;
	t_list	*new;

	first = 0;
	if (lst)
	{
		if (!(first = ft_lstnew(lst->content, lst->content_size)))
			return (0);
		first = f(first);
		list = first;
		lst = lst->next;
	}
	while (lst)
	{
		if (!(new = ft_lstnew(lst->content, lst->content_size)))
			return (0);
		new = f(new);
		list->next = new;
		lst = lst->next;
	}
	return (first);
}
