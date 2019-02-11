/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:15:43 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/27 16:48:32 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!(ret = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	while (s1[i] && i < n)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
