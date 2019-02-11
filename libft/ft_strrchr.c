/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:16:05 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/07 16:40:03 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	int		i;
	char	*last;

	last = 0;
	i = 0;
	len = 0;
	while (s[len])
		len++;
	len++;
	while (i < len)
	{
		if (s[i] == c)
			last = ((char*)&s[i]);
		i++;
	}
	return (last);
}
