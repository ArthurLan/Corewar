/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:27:11 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:13:54 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_digit(char *flag, char *ret)
{
	int		i;
	int		nb;

	i = -1;
	while (flag[++i])
		if (ft_isdigit(flag[i]) && flag[i] != '0' && flag[i - 1] != '.')
		{
			if (!ft_strchr(flag, '-'))
			{
				nb = ft_atoi(&flag[i]);
				while (ft_strlen(ret) < (size_t)nb)
					ret = add_begin(ret, ft_strdup(" "));
			}
			flag = replace_chars(flag, ft_itoa(ft_atoi(&flag[i])), NULL);
			return (handle_conversion(flag, ret));
		}
	return (0);
}
