/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:25:42 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/10 14:20:40 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = malloc(sizeof(t_list))))
		return (0);
	if (content == 0)
	{
		list->content = 0;
		list->content_size = 0;
	}
	else
	{
		if (!(list->content = ft_memalloc(content_size)))
			return (0);
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = 0;
	return (list);
}
