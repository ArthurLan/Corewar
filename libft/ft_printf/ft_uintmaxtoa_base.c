/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:34:34 by clecalie          #+#    #+#             */
/*   Updated: 2017/12/14 15:51:52 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length(uintmax_t n, int base)
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

char		*ft_uintmaxtoa_base(uintmax_t n, int base)
{
	int		i;
	char	*str;
	char	*base_str;

	base_str = "0123456789ABCDEF";
	i = 0;
	if (!(str = ft_strnew(get_length(n, base))))
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (n != 0)
	{
		str[i++] = base_str[(n % base)];
		n /= base;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}
