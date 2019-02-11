/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:30:41 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 13:48:16 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (j < n && s2[j])
	{
		if (s2[j])
			s1[i] = s2[j];
		else
			s1[i] = '\0';
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
