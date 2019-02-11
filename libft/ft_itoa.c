/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:34:34 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/01 16:15:10 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	get_length(int n)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	if (len <= 0)
		len = 1;
	return (len);
}

char		*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*str;

	nb = (long)n;
	i = 0;
	if (!(str = ft_strnew(get_length(n))))
		return (0);
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		nb = -nb;
	while (nb != 0)
	{
		str[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
