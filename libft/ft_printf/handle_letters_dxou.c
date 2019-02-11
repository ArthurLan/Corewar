/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_letters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:13:35 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/19 11:52:59 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_di(char flag_letter, char *ret,
		char *length_flag, va_list *args)
{
	if (!ft_strcmp(length_flag, "l") || flag_letter == 'D')
		ret = ft_intmaxtoa(va_arg(*args, long));
	else if (!ft_strcmp(length_flag, "hh"))
		ret = ft_itoa((signed char)va_arg(*args, int));
	else if (!ft_strcmp(length_flag, "h"))
		ret = ft_itoa((short)va_arg(*args, int));
	else if (!ft_strcmp(length_flag, "ll"))
		ret = ft_intmaxtoa(va_arg(*args, long long));
	else if (!ft_strcmp(length_flag, "j"))
		ret = ft_intmaxtoa(va_arg(*args, intmax_t));
	else if (!ft_strcmp(length_flag, "z"))
		ret = ft_intmaxtoa(va_arg(*args, size_t));
	else
		ret = ft_itoa(va_arg(*args, int));
	return (ret);
}

char	*handle_x(char flag_letter, char *ret, char *length_flag, va_list *args)
{
	char	*t;

	if (!ft_strcmp(length_flag, "hh"))
		ret = ft_itoa_base((unsigned char)va_arg(*args, int), 16);
	else if (!ft_strcmp(length_flag, "h"))
		ret = ft_itoa_base((unsigned short)va_arg(*args, int), 16);
	else if (!ft_strcmp(length_flag, "l"))
		ret = ft_uintmaxtoa_base(va_arg(*args, unsigned long), 16);
	else if (!ft_strcmp(length_flag, "ll"))
		ret = ft_uintmaxtoa_base(va_arg(*args, unsigned long long), 16);
	else if (!ft_strcmp(length_flag, "j"))
		ret = ft_uintmaxtoa_base(va_arg(*args, uintmax_t), 16);
	else if (!ft_strcmp(length_flag, "z"))
		ret = ft_uintmaxtoa_base(va_arg(*args, size_t), 16);
	else
		ret = ft_itoa_base(va_arg(*args, unsigned int), 16);
	if (flag_letter == 'x')
	{
		t = ft_strtolower(ret);
		ft_strdel(&ret);
		ret = t;
	}
	return (ret);
}

char	*handle_o(char flag_letter, char *ret, char *length_flag, va_list *args)
{
	if (!ft_strcmp(length_flag, "l") || flag_letter == 'O')
		ret = ft_uintmaxtoa_base(va_arg(*args, unsigned long), 8);
	else if (!ft_strcmp(length_flag, "hh"))
		ret = ft_itoa_base((unsigned char)va_arg(*args, int), 8);
	else if (!ft_strcmp(length_flag, "h"))
		ret = ft_itoa_base((unsigned short)va_arg(*args, int), 8);
	else if (!ft_strcmp(length_flag, "ll"))
		ret = ft_uintmaxtoa_base(va_arg(*args, unsigned long long), 8);
	else if (!ft_strcmp(length_flag, "j"))
		ret = ft_uintmaxtoa_base(va_arg(*args, uintmax_t), 8);
	else if (!ft_strcmp(length_flag, "z"))
		ret = ft_uintmaxtoa_base(va_arg(*args, unsigned long long), 8);
	else
		ret = ft_itoa_base(va_arg(*args, unsigned int), 8);
	return (ret);
}

char	*handle_u(char flag_letter, char *ret, char *length_flag, va_list *args)
{
	if (!ft_strcmp(length_flag, "l") || flag_letter == 'U')
		ret = ft_uintmaxtoa(va_arg(*args, unsigned long));
	else if (!ft_strcmp(length_flag, "hh"))
		ret = ft_itoa((unsigned char)va_arg(*args, int));
	else if (!ft_strcmp(length_flag, "h"))
		ret = ft_itoa((unsigned short)va_arg(*args, int));
	else if (!ft_strcmp(length_flag, "ll"))
		ret = ft_uintmaxtoa(va_arg(*args, unsigned long long));
	else if (!ft_strcmp(length_flag, "j"))
		ret = ft_uintmaxtoa(va_arg(*args, uintmax_t));
	else if (!ft_strcmp(length_flag, "z"))
		ret = ft_uintmaxtoa(va_arg(*args, unsigned long long));
	else
		ret = ft_intmaxtoa(va_arg(*args, unsigned int));
	return (ret);
}
