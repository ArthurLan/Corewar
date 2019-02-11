/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:28:03 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/17 14:39:37 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_space(char *flag, char *ret)
{
	int		i;
	char	flag_letter;

	i = -1;
	flag_letter = flag[ft_strlen(flag) - 1];
	while (flag[++i])
		if (flag[i] == ' ')
		{
			if (ft_strchr("id", flag_letter) && !ft_strchr(flag, '+')
					&& ft_atoi(ret) >= 0)
				ret = add_begin(ret, ft_strdup(" "));
			while (ft_strchr(flag, ' '))
				flag = replace_chars(flag, ft_strdup(" "), ft_strdup(""));
			return (handle_conversion(flag, ret));
		}
	return (0);
}
