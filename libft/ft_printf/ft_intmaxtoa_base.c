/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmaxtoa_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 12:11:47 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:26:13 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(intmax_t n, int base)
{
	int		len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	if (len <= 0)
		len = 1;
	return (len);
}

char		*ft_intmaxtoa_base(intmax_t n, int base)
{
	int		i;
	char	*str;
	char	*base_str;
	int		neg;

	base_str = "0123456789ABCDEF";
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = ft_strnew(get_length(n, base))))
		return (0);
	if (n < 0 && base == 10)
	{
		n = -n;
		neg = 1;
	}
	while (n != 0)
	{
		str[i++] = base_str[(n % base)];
		n /= base;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
