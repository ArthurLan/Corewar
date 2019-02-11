/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:40:17 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 14:06:24 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (!needle[0])
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i] && needle[j] &&
				i < len && haystack[i] - needle[j] == 0)
		{
			i++;
			j++;
		}
		if (!needle[j])
			return ((char*)&haystack[i - j]);
		i -= j;
		i++;
	}
	return (0);
}
