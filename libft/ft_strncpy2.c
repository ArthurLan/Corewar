/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:18:05 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/22 10:18:07 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strncpy2(char *dest, char *arc, unsigned int n)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = dest;
	while (i < n && arc[i] != '\0')
	{
		temp[i] = arc[i];
		i++;
	}
	temp[i] = '\0';
	return (dest);
}
