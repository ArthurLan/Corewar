/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:11:42 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/08 15:40:01 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;

	if (!(s = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	ft_bzero(s, size);
	s[size] = '\0';
	return (s);
}
