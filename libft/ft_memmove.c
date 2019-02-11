/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:55:47 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 12:11:33 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst2;
	char	*src2;
	char	*temp;

	dst2 = (char*)dst;
	src2 = (char*)src;
	if (!(temp = (char*)malloc(sizeof(char) * len)))
		return (dst);
	i = 0;
	while (i < len)
	{
		temp[i] = src2[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		dst2[i] = temp[i];
		i++;
	}
	return (dst);
}
