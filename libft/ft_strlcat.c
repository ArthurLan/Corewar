/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:30:41 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 13:53:26 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	if (size == 0)
		return (ft_strlen(dst));
	i = 0;
	while (dst[i] && i < size)
		i++;
	length = i;
	while (src[i - length] && i < size - 1)
	{
		dst[i] = src[i - length];
		i++;
	}
	if (length < size)
		dst[i] = '\0';
	return (length + ft_strlen(src));
}
