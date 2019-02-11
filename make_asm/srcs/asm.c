/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_all_info	*ft_init(int fd)
{
	t_all_info *info;

	if (!(info = (t_all_info*)malloc(sizeof(t_all_info))))
		return (0);
	info->name = NULL;
	info->commentaire = NULL;
	info->head_inst = NULL;
	info->size = 0;
	info->fd = fd;
	info->nb_line = 1;
	info->ret = 1;
	info->error = 1;
	return (info);
}

void		pars_liste(t_all_info *all, char *argv)
{
	int ok;

	if (!all->head_inst && !all->commentaire && !all->name)
		ok = 16;
	else if (!all->commentaire)
		ok = 13;
	else if (!all->name)
		ok = 14;
	else if (all->size > CHAMP_MAX_SIZE)
		ok = 15;
	else
		ok = label_exist(all);
	if (ok == 1)
		write_cor_file(all, argv);
	else
		error(ok, all->nb_line);
}

int			security(char *str)
{
	if (str[ft_strlen(str) - 1] != 's'
		|| str[ft_strlen(str) - 2] != '.')
	{
		ft_putstr_fd("Bad file extension\n", 2);
		return (0);
	}
	return (1);
}

void		pars_file(t_all_info *all)
{
	char		*line;
	int			in_header;

	in_header = 1;
	line = NULL;
	while (get_next_line(all->fd, &line) > 0)
	{
		if (all->error == 1)
			all->error = ft_all(&line, all, &in_header);
		if (all->ret < 1)
			break ;
		ft_strdel(&line);
	}
	if (ft_strlen(line) > 0)
		ft_strdel(&line);
}

int			main(int argc, char **argv)
{
	t_all_info	*all;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./asm <sourcefile.s>\n", 2);
		return (0);
	}
	if (security(argv[1]))
	{
		all = ft_init(open(argv[1], O_RDONLY | O_NOFOLLOW));
		pars_file(all);
		if (all->error == 1)
			pars_liste(all, argv[1]);
		del_all_info(all);
	}
	return (0);
}
