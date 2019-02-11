/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:20:30 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/25 11:29:48 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*remove_0(char *flag)
{
	int		i;

	i = 0;
	while (flag[i])
	{
		if (flag[i] == '0' && !ft_isdigit(flag[i - 1]))
			flag = replace_chars(flag, ft_strdup("0"), ft_strdup(""));
		i++;
	}
	return (flag);
}

static char	*precision_cs(char *ret, int nb, char flag_letter)
{
	if (nb == 0 && ret[0] == '@')
		nb = 1;
	else if (flag_letter == 'S' && nb > 0)
	{
		if (nb > 1 && nb < (int)ft_strlen(ret))
		{
			if ((unsigned char)ret[nb - 1] >= 192 && MB_CUR_MAX > 1)
				nb--;
			else if ((unsigned char)ret[nb - 2] >= 192)
				nb -= 2;
		}
	}
	ret = ft_strndup_static(ret, nb);
	return (ret);
}

static char	*store_begin(char *ret, int nb)
{
	char	*temp;
	char	*lower1;
	char	*lower2;

	temp = 0;
	lower1 = ft_strtolower(ret);
	lower2 = ft_strtolower("0x");
	if (ft_strncmp(lower1, lower2, 2) == 0)
	{
		temp = ft_strdup(!ft_strncmp(ret, "0x", 2) ? "0x" : "0X");
		ret = ft_update(&ret, &ret[2]);
	}
	else if (ft_strchr(ret, '-'))
	{
		temp = ft_strdup("-");
		ret = ft_update(&ret, &ret[1]);
	}
	while (ft_strlen(ret) < (size_t)nb)
		ret = add_begin(ret, ft_strdup("0"));
	if (temp)
		ret = add_begin(ret, temp);
	ft_strdel(&lower1);
	ft_strdel(&lower2);
	return (ret);
}

static char	*get_ret_value(char *ret, int nb, char *flag)
{
	char	flag_letter;

	flag_letter = flag[ft_strlen(flag) - 1];
	if (ft_strchr("diuopOxX", flag_letter) && nb > 0)
		ret = store_begin(ret, nb);
	else if (ft_strchr("csS", flag_letter))
		ret = precision_cs(ret, nb, flag_letter);
	else if (ft_strchr("oO", flag_letter) && nb == 0
			&& ft_strequ(ret, "0") && ft_strchr(flag, '#'))
		ret = ft_strdup("0");
	else if (ft_strchr("xXudioO", flag_letter)
			&& nb == 0 && ft_strequ(ret, "0"))
		ret = ft_strdup("");
	else if (flag_letter == 'p' && nb == 0
			&& ft_strequ(ft_strtolower(ret), "0x0"))
		ret = ft_strndup(ret, 2);
	return (ret);
}

char		*handle_precision(char *flag, char *ret)
{
	int				i;
	int				nb;
	char			flag_letter;

	i = -1;
	flag_letter = flag[ft_strlen(flag) - 1];
	while (flag[++i])
		if (flag[i] == '.')
		{
			nb = ft_atoi(&flag[i + 1]);
			ret = get_ret_value(ret, nb, flag);
			flag = replace_chars(flag,
					get_0_param(&flag[i + 1]), ft_strdup(""));
			if (ft_strchr("diuopOxX", flag_letter))
				flag = remove_0(flag);
			flag = replace_chars(flag, ft_strdup("."), ft_strdup(""));
			return (handle_conversion(flag, ret));
		}
	return (0);
}
