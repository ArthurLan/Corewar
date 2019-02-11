/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_in_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/30 14:21:38 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_header(t_all_info *all, char *next, int id)
{
	char	*tmp;

	if (id == 0)
		if (!all->name)
			all->name = ft_strdup(next);
		else
		{
			tmp = ft_strjoin(all->name, next);
			ft_strdel(&all->name);
			all->name = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	else
	{
		if (!all->commentaire)
			all->commentaire = ft_strdup(next);
		else
		{
			tmp = ft_strjoin(all->commentaire, next);
			ft_strdel(&all->commentaire);
			all->commentaire = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	ft_strdel(&next);
}

int		write_and_free_header(t_all_info *all, char *name,
			char **other_line, int id)
{
	char	*fullname;
	int		index;
	int		error;

	index = ft_strniels(name, '"');
	if (index == -1)
		fullname = ft_strjoin(name, "\n");
	else
		fullname = ft_strsub(name, 0, index);
	error = check_comm(&name[index + 1]);
	write_header(all, fullname, id);
	ft_strdel(&name);
	ft_strdel(other_line);
	return (error);
}

int		comm_after(char *str)
{
	int		index;
	char	*tmp;
	int		ok;

	index = ft_strniels(str, '"');
	if (index == -1)
		return (0);
	tmp = no_space(str);
	index = ft_strniels(tmp, '"');
	if (tmp[index + 1] && tmp[index + 1] != COMMENT_CHAR)
		ok = 0;
	else
		ok = 1;
	ft_strdel(&tmp);
	return (ok);
}

char	*init_name(char *str)
{
	if (str[1])
		return (ft_strdup(&str[1]));
	else
		return (ft_strdup("\0"));
}

int		keep_name(char *line, int id, t_all_info *all)
{
	char	*name;
	char	*other_line;

	other_line = ft_strdup(line);
	name = init_name(ft_strchr(line, '"'));
	while (ft_strniels(name, '"') == -1
		&& ft_strlen(all->commentaire) <= COMMENT_LENGTH
		&& ft_strlen(all->name) <= PROG_NAME_LENGTH && ft_strcmp(name, "\""))
	{
		if (id == 0)
			return (free_and_return(name, other_line, 17));
		write_and_free_header(all, name, &other_line, id);
		if (get_next_line(all->fd, &other_line) <= 0)
			return (17);
		name = ft_strdup(other_line);
		all->nb_line += 1;
	}
	if (!comm_after(name) && !ft_strcmp(name, "\""))
		return (free_and_return(name, other_line, 8));
	return (write_and_free_header(all, name, &other_line, id));
}
