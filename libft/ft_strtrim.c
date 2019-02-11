/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:41:09 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/10 14:20:07 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(s) - 1;
	if (!s)
		return (0);
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	if ((end - start) < 0)
		return ("");
	if (!(str = ft_strnew(end - start + 1)))
		return (0);
	while (start <= end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
