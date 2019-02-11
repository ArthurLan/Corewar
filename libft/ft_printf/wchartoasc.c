/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchartoasc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:05:27 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/31 12:57:22 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Gestion des masques.
** 0XXXXXXX -> Si le caractère est inférieure ou égal à 127
** 110XXXXX 10XXXXXX -> Si le caractère est entre 128 et 2047 (size 11)
** 1110XXXX 10XXXXXX 10XXXXXX -> Si le caractère est entre 2048
** et 65535 (size 16)
** 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX -> Si le caractère est
** entre 65536 et 2097151 (size 21)
**
** Les 3 masques: 0xC080 / 0xE08080 / 0xF0808080
*/

static char	*get_size_11(unsigned int c)
{
	char			*ret;

	ret = ft_strnew(2);
	ret[0] = (c >> 6) | 0xC0;
	ret[1] = (c & 63) | 0x80;
	return (ret);
}

static char	*get_size_16(unsigned int c)
{
	char			*ret;

	ret = ft_strnew(3);
	ret[0] = (c >> 12) | 0xE0;
	ret[1] = (c >> 6 & 63) | 0x80;
	ret[2] = (c & 63) | 0x80;
	return (ret);
}

static char	*get_size_21(unsigned int c)
{
	char			*ret;

	ret = ft_strnew(4);
	ret[0] = (c >> 18) | 0xF0;
	ret[1] = (c >> 12 & 63) | 0x80;
	ret[2] = (c >> 6 & 63) | 0x80;
	ret[3] = (c & 63) | 0x80;
	return (ret);
}

static char	*get_unicode(int c)
{
	char	*ret;

	if (c <= 0x7F)
	{
		ret = ft_strnew(1);
		ret[0] = c;
		return (ret);
	}
	else if ((c >= 0xD800 && c <= 0xDB7F) || (c >= 0xDC00 && c <= 0xDFFF))
		return (ft_ctos(-1));
	else if (c > 0x7F && c <= 0xFF && MB_CUR_MAX == 1)
		return (get_unicode((char)c));
	else if (c > 0x7F && c <= 0xFF && MB_CUR_MAX > 1)
		return (get_size_11(c));
	else if (c <= 0x7FF && MB_CUR_MAX > 1)
		return (get_size_11(c));
	else if (c <= 0xFFFF && MB_CUR_MAX > 2)
		return (get_size_16(c));
	else if (c <= 0x10FFFF && MB_CUR_MAX > 3)
		return (get_size_21(c));
	else
		return (ft_ctos(-1));
}

char		*wchartoasc(wchar_t *str)
{
	int				i;
	int				c;
	char			*ret;
	char			*temp;

	if (!str)
		return (0);
	i = -1;
	ret = ft_strnew(0);
	while (str[++i])
	{
		c = str[i];
		temp = get_unicode(c);
		if (c > 0x0)
			ret = add_end(ret, temp);
		else
			ret = add_end(ret, ft_ctos(-1));
	}
	return (ret);
}
