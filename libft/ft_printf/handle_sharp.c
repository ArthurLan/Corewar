/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sharp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:25:23 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/17 14:41:58 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_sharp(char *flag, char *ret)
{
	int		i;
	char	flag_letter;

	i = -1;
	flag_letter = flag[ft_strlen(flag) - 1];
	while (flag[++i])
		if (flag[i] == '#')
		{
			if (!ft_strequ(ret, "0") && !ft_strequ(ret, ""))
			{
				if (flag_letter == 'x')
					ret = add_begin(ft_strtolower(ret), ft_strdup("0x"));
				else if (flag_letter == 'X')
					ret = add_begin(ret, ft_strdup("0X"));
				else if ((flag_letter == 'o' || flag_letter == 'O')
						&& ret[0] != '0')
					ret = add_begin(ret, ft_strdup("0"));
			}
			while (ft_strchr(flag, '#'))
				flag = replace_chars(flag, ft_strdup("#"), ft_strdup(""));
			return (handle_conversion(flag, ret));
		}
	return (0);
}
