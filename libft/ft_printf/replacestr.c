/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacestr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:51:09 by clecalie          #+#    #+#             */
/*   Updated: 2018/01/24 10:24:55 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*replacestr(char *dest, char *find, char *content)
{
	char	*after_find;
	char	*temp;

	if (!(after_find = ft_strstr(dest, find)))
		return (dest);
	after_find = ft_strdup(&after_find[ft_strlen(find)]);
	temp = ft_strnew(0);
	temp = add_end(temp, ft_strndup(dest, ft_strlen(dest)
				- ft_strlen(after_find) - ft_strlen(find)));
	if (content)
		temp = add_end(temp, content);
	else if (find[ft_strlen(find) - 1] == 's')
		temp = add_end(temp, "(null)");
	temp = add_end(temp, after_find);
	dest = ft_strdup(temp);
	ft_strdel(&temp);
	ft_strdel(&find);
	return (dest);
}

char	*replace_chars(char *dest, char *find, char *content)
{
	char		*part;
	size_t		i;
	size_t		j;
	size_t		length;
	char		*part2;

	part = ft_strstr(dest, find);
	part2 = &part[ft_strlen(find)];
	length = ft_strlen(dest) - ft_strlen(part);
	i = length;
	j = 0;
	while (i - length < ft_strlen(find))
		if (content && content[j])
			dest[i++] = content[j++];
		else
			break ;
	j = 0;
	while (part2[j])
		dest[i++] = part2[j++];
	dest[i] = '\0';
	ft_strdel(&find);
	ft_strdel(&content);
	return (dest);
}
