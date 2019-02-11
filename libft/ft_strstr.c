/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:40:17 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 14:05:32 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = 0;
	if (!needle[0])
		return ((char*)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] && needle[j] && haystack[i] == needle[j])
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
