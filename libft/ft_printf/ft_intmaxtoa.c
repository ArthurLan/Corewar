/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:34:34 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:25:35 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(intmax_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	if (len <= 0)
		len = 1;
	return (len);
}

char		*ft_intmaxtoa(intmax_t n)
{
	int			i;
	char		*str;
	uintmax_t	nb;

	i = 0;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	if (!(str = ft_strnew(get_length(n))))
		return (0);
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
