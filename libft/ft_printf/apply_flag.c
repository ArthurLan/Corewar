/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 10:51:46 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/31 14:23:53 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern char	*g_buffer;

static char	*get_temp(char *ret, char **temp, char flag_letter)
{
	*temp = 0;
	if (ret == NULL && (flag_letter == 's' || flag_letter == 'S'))
		ret = ft_strdup("(null)");
	else if (ret && ft_strchr(ret, -1) && ft_strchr("CS", flag_letter))
		return (ret);
	else if (ret && ret[0] == '\0' && ft_strchr("cC", flag_letter))
	{
		*temp = ft_strdup("@");
		ft_strdel(&ret);
		ret = ft_strdup("@");
	}
	else if (!ft_strchr("sSpdDioOuUxXcC%", flag_letter))
	{
		ft_strdel(&ret);
		ret = ft_ctos(flag_letter);
	}
	return (ret);
}

static void	print_content(char *temp,
		char *conversion, char flag_letter)
{
	int		j;

	if (ft_strchr("cC", flag_letter) && temp && temp[0] == '@')
	{
		j = 0;
		while (conversion[j])
		{
			if (conversion[j] == '@')
				ft_putchar(0);
			else
				ft_putchar(conversion[j]);
			j++;
		}
	}
	else if (ft_strlen(conversion))
		ft_putstr(conversion);
}

static int	apply_conversion(char **flag, char **ret, char **temp, char **str)
{
	char	*t_flag;
	char	*conversion;
	char	flag_letter;
	int		len;

	t_flag = ft_strdup(*flag);
	flag_letter = t_flag[ft_strlen(t_flag) - 1];
	conversion = handle_conversion(*flag, *ret);
	*str = replacestr(*str, t_flag, ft_strdup(conversion));
	if (conversion && ft_strchr(conversion, -1) &&
			ft_strchr("CS", flag_letter))
		ft_strdel(str);
	else
	{
		ft_putstr(g_buffer);
		ft_strdel(&g_buffer);
		g_buffer = ft_strnew(0);
		print_content(*temp, conversion, flag_letter);
		ft_strdel(temp);
	}
	len = (int)ft_strlen(conversion);
	ft_strdel(&conversion);
	return (len);
}

char		*apply_flag(char *flag, char *str, int *i, va_list *args)
{
	char	*temp;
	char	*ret;
	char	*length_f;
	char	flag_letter;

	length_f = get_length_flag(flag);
	flag_letter = flag[ft_strlen(flag) - 1];
	ret = handle_flags(length_f, flag, args);
	ret = get_temp(ret, &temp, flag[ft_strlen(flag) - 1]);
	ft_strdel(&length_f);
	*i += apply_conversion(&flag, &ret, &temp, &str) - 1;
	return (str);
}
