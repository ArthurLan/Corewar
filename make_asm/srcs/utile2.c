/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:42:41 by ncohen            #+#    #+#             */
/*   Updated: 2018/12/03 14:42:45 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*label_without_comm(char *str)
{
	int		i;
	char	*no_space;

	no_space = ft_strtrim(str);
	i = -1;
	while (no_space[++i])
	{
		if (no_space[i] == LABEL_CHAR)
		{
			if (no_space[i + 1] == COMMENT_CHAR)
			{
				str[i] = '\0';
				ft_strdel(&no_space);
				return (str);
			}
			else if (!no_space[i + 1])
			{
				str[i] = '\0';
				ft_strdel(&no_space);
				return (str);
			}
		}
	}
	ft_strdel(&no_space);
	return (str);
}

char		**in_next_line(char *line, int index)
{
	char	**info;
	int		i;

	info = ft_split_whitespaces(line);
	if (!info[1])
	{
		free_double_tab(info);
		return (NULL);
	}
	i = all_param(info, index);
	if ((info[++i + index] && info[i + index][0] != COMMENT_CHAR) || i == -1)
	{
		free_double_tab(info);
		return (NULL);
	}
	return (info);
}

t_label		*write_label(char *str)
{
	t_label	*label;

	if (!(label = (t_label*)malloc(sizeof(t_label))))
		return (0);
	label->label = ft_strdup(str);
	return (label);
}

char		*ft_strtronc(char *str, int n)
{
	char	*new;
	int		i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int			free_and_return(char *name, char *other_line, int to_return)
{
	ft_strdel(&other_line);
	ft_strdel(&name);
	return (to_return);
}
