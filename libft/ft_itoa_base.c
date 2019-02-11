/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:34:34 by clecalie          #+#    #+#             */
/*   Updated: 2017/12/13 13:51:00 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	get_length(long n, int base)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	if (len <= 0)
		len = 1;
	return (len);
}

char		*ft_itoa_base(long n, int base)
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
		ft_strdel(&str);
		str = ft_strdup("0");
		return (str);
	}
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		str[i++] = base_str[(n % base)];
		n /= base;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
