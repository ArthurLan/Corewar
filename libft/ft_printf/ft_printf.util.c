/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:33:57 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/26 13:56:12 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_flag(char *str)
{
	int		i;
	char	*validchar;

	validchar = " +-#0123456789.hljz";
	i = 1;
	while (str[i])
	{
		if (ft_strchr(validchar, str[i]))
			i++;
		else
			return (ft_strndup(str, i + 1));
	}
	return (ft_strdup(str));
}

char	*get_length_flag(char *flag)
{
	char	*valid;
	int		i;
	int		j;
	char	*ret;

	ret = 0;
	valid = "hljz";
	i = 0;
	while (!ft_strchr(valid, flag[i]))
		i++;
	if (flag[i])
	{
		j = i;
		while (ft_strchr(valid, flag[j]))
			j++;
		ret = ft_strsub(flag, i, j - i);
	}
	return (ret);
}

char	*ft_update(char **old, char *new)
{
	char	*temp;

	temp = ft_strdup(new);
	ft_strdel(old);
	*old = temp;
	return (*old);
}

char	*ft_strndup_static(char *str, size_t n)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (i >= n)
		{
			str[i] = '\0';
		}
		i++;
	}
	return (str);
}
