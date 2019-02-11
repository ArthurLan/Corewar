/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 17:01:30 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/08 17:01:32 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_list_push_front(t_list **begin_list, void *data, size_t len)
{
	t_list	*list;

	if (*begin_list)
	{
		list = ft_lstnew(data, len);
		list->next = *begin_list;
		*begin_list = list;
	}
	else
		*begin_list = ft_lstnew(data, len);
}
