/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:27:41 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/17 14:38:53 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_plus(char *flag, char *ret)
{
	int		i;
	char	flag_letter;

	i = -1;
	flag_letter = flag[ft_strlen(flag) - 1];
	while (flag[++i])
		if (flag[i] == '+')
		{
			if (ft_strchr("id", flag_letter) && ft_atol(ret) >= 0)
				ret = add_begin(ret, ft_strdup("+"));
			while (ft_strchr(flag, '+'))
				flag = replace_chars(flag, ft_strdup("+"), ft_strdup(""));
			while (ft_strchr(flag, ' '))
				flag = replace_chars(flag, ft_strdup(" "), ft_strdup(""));
			return (handle_conversion(flag, ret));
		}
	return (0);
}
