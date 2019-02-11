/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 10:09:10 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:11:10 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*get_0_param(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (ft_strndup(str, i));
}

char			*handle_conversion(char *flag, char *ret)
{
	char	*rep;

	if (!ret)
		return (0);
	rep = 0;
	if (ft_strcmp(flag, "%%") == 0)
		return (ret);
	if ((rep = handle_precision(flag, ret)))
		return (rep);
	else if ((rep = handle_sharp(flag, ret)))
		return (rep);
	else if ((rep = handle_plus(flag, ret)))
		return (rep);
	else if ((rep = handle_space(flag, ret)))
		return (rep);
	else if ((rep = handle_neg(flag, ret)))
		return (rep);
	else if ((rep = handle_zero(flag, ret)))
		return (rep);
	else if ((rep = handle_digit(flag, ret)))
		return (rep);
	return (ret);
}

char			*handle_other_flags(char *flag, va_list *args)
{
	char	*ret;
	wchar_t	*ret_w;
	char	flag_letter;
	char	*t;

	ret = 0;
	flag_letter = flag[ft_strlen(flag) - 1];
	if (flag_letter == 'p')
	{
		t = ft_itoa_base(va_arg(*args, long int), 16);
		ret = add_begin(ft_strtolower(t), ft_strdup("0x"));
		ft_strdel(&t);
	}
	else if (flag_letter == 'S')
	{
		ret_w = va_arg(*args, wchar_t*);
		ret = wchartoasc(ret_w);
	}
	else if (flag_letter == 'C')
	{
		ret_w = ft_ctos_up(va_arg(*args, wchar_t));
		ret = wchartoasc(ret_w);
		free(ret_w);
	}
	return (ret);
}

char			*handle_flags(char *length_flag, char *flag, va_list *args)
{
	char	*ret;
	char	flag_letter;

	ret = 0;
	flag_letter = flag[ft_strlen(flag) - 1];
	if (flag_letter == '%' && flag[0] == '%' && flag[1])
		ret = ft_strdup("%");
	else if (flag_letter == 'd' || flag_letter == 'i' || flag_letter == 'D')
		ret = handle_di(flag_letter, ret, length_flag, args);
	else if (flag_letter == 'x' || flag_letter == 'X')
		ret = handle_x(flag_letter, ret, length_flag, args);
	else if (flag_letter == 'o' || flag_letter == 'O')
		ret = handle_o(flag_letter, ret, length_flag, args);
	else if (flag_letter == 'u' || flag_letter == 'U')
		ret = handle_u(flag_letter, ret, length_flag, args);
	else if (flag_letter == 's')
		ret = handle_s(flag, ret, length_flag, args);
	else if (flag_letter == 'c')
		ret = handle_c(flag, ret, length_flag, args);
	else
		ret = handle_other_flags(flag, args);
	return (ret);
}
