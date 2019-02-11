/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:16:05 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/03 15:48:22 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		len;
	int		i;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[len])
		len++;
	len++;
	while (i < len)
	{
		if (s[i] == c)
			return ((char*)&s[i]);
		i++;
	}
	return (0);
}
