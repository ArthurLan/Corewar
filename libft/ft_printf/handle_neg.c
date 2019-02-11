/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_neg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:26:08 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:12:56 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define ABS(value) value < 0 ? -value : value

static char	*remove_useless_flag(char *flag, int idx)
{
	if (ft_isdigit(flag[idx + 1]) && flag[idx + 1] != '0')
		flag = replace_chars(flag, ft_itoa(ft_atoi(&flag[idx])), NULL);
	else if (flag[idx + 1] == '0')
		flag = replace_chars(flag, add_end(ft_strdup("-"), ft_strdup("0")),
				NULL);
	else
		flag = replace_chars(flag, ft_strdup("-"), NULL);
	return (flag);
}

static char	*update_nb(char *flag, int *nb)
{
	int		j;

	j = -1;
	while (flag[++j])
		if (ft_isdigit(flag[j]) && flag[j] != 0)
		{
			if (*nb == 0)
				*nb = ft_atoi(&flag[j]);
			flag = replace_chars(flag, ft_itoa(ft_atoi(&flag[j])), NULL);
			break ;
		}
	return (flag);
}

char		*handle_neg(char *flag, char *ret)
{
	int		i;
	int		nb;

	i = -1;
	while (flag[++i])
		if (flag[i] == '-')
		{
			nb = ABS(ft_atoi(&flag[i + 1]));
			flag = update_nb(flag, &nb);
			while (ft_strlen(ret) < (size_t)(nb))
				ret = add_end(ret, ft_strdup(" "));
			flag = remove_useless_flag(flag, i);
			i = -1;
			while (flag[++i])
				if (flag[i] == '0' && !ft_isdigit(flag[i - 1]))
					flag = replace_chars(flag, get_0_param(&flag[i]), NULL);
			return (handle_conversion(flag, ret));
		}
	return (0);
}
