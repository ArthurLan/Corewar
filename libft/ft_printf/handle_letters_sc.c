/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_letters_sc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:25:06 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/18 13:55:19 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_s(char *flag, char *ret, char *length_flag, va_list *args)
{
	if (!ft_strcmp(length_flag, "l"))
	{
		flag = replacestr(flag, ft_strdup("s"), ft_strdup("S"));
		return (handle_other_flags(flag, args));
	}
	else
		ret = ft_strdup(va_arg(*args, char*));
	return (ret);
}

char	*handle_c(char *flag, char *ret, char *length_flag, va_list *args)
{
	if (!ft_strcmp(length_flag, "l"))
	{
		flag = replacestr(flag, ft_strdup("c"), ft_strdup("C"));
		return (handle_other_flags(flag, args));
	}
	else
		ret = ft_ctos(va_arg(*args, int));
	return (ret);
}
