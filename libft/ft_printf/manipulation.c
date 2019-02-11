/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:56:47 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:24:28 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_begin(char *str, char *add)
{
	char	*ret;

	if (!str || !add)
		return (0);
	if (!(ret = ft_strnew(ft_strlen(str) + ft_strlen(add) + 1)))
		return (0);
	ft_strcat(ret, add);
	ft_strcat(ret, str);
	if (ft_strlen(str) > 0)
		ft_strdel(&str);
	ft_strdel(&add);
	return (ret);
}

char	*add_end(char *str, char *add)
{
	char	*ret;

	if (!str || !add)
		return (0);
	if (!(ret = ft_strnew(ft_strlen(str) + ft_strlen(add) + 1)))
		return (0);
	ft_strcat(ret, str);
	ft_strcat(ret, add);
	ft_strdel(&str);
	ft_strdel(&add);
	return (ret);
}
