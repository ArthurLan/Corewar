/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:34:19 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 13:47:21 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	size_t	i;
	char	*dst2;
	char	*src2;

	i = 0;
	dst2 = (char*)dst;
	src2 = (char*)src;
	while (i < n)
	{
		if (src2[i] != c)
			dst2[i] = src2[i];
		else
		{
			dst2[i] = src2[i];
			return ((void*)&dst2[i + 1]);
		}
		i++;
	}
	return (0);
}
