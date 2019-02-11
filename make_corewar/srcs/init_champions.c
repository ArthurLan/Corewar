/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:39:20 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/21 13:39:21 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			is_valid_champ_id(t_list **head, int champ_id)
{
	t_list	*list;
	t_champ	*champ;

	list = *head;
	if (champ_id <= 0)
		return (0);
	while (list)
	{
		champ = (t_champ*)list->content;
		if (champ->id == (unsigned int)-ABS(champ_id))
			return (0);
		list = list->next;
	}
	return (1);
}

int			store_champ_content(int fd, t_champ *champ)
{
	unsigned char	buff[CHAMP_MAX_SIZE + 1];
	int				buff_len;

	buff_len = read(fd, buff, champ->header->prog_size);
	if (buff_len != (int)champ->header->prog_size)
	{
		ft_putendl_fd("The champ size differ from what the header says", 2);
		free(champ->header);
		free(champ);
		return (0);
	}
	champ->content = ft_ustrsub(buff, 0, champ->header->prog_size);
	return (1);
}

t_champ		*store_champions(int fd, int champ_id)
{
	unsigned char	buff[HEAD_SIZE + 1];
	int				buff_len;
	t_champ			*champ;
	static int		color = 1;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (0);
	champ->id = -(ABS(champ_id));
	champ->nb_live = 0;
	champ->is_alive = 1;
	champ->color = color;
	color++;
	buff_len = read(fd, buff, HEAD_SIZE);
	if (buff_len == HEAD_SIZE)
		champ->header = parse_header(buff);
	else
	{
		ft_putendl_fd("Invalid champion.", 2);
		free(champ);
		return (0);
	}
	if (!store_champ_content(fd, champ))
		return (0);
	return (champ);
}

int			ft_valid_champ(t_env *env, char **argv, int i, int fd)
{
	int		champ_id;
	t_champ	*champ;

	champ = NULL;
	if (i - 2 > 0 && ft_strequ("-n", argv[i - 2]))
		champ_id = ft_atoi(argv[i - 1]);
	else
		champ_id = env->nb_champs + 1;
	if (!is_valid_champ_id(&(env->head_champs), champ_id))
	{
		ft_putstr_fd("Invalid champion number, ", 2);
		ft_putstr_fd("it must be positive or unique.\n", 2);
		return (0);
	}
	env->nb_champs++;
	if (env->nb_champs > MAX_PLAYERS)
	{
		ft_putendl_fd("There is too many champions.", 2);
		return (0);
	}
	if (!(champ = store_champions(fd, champ_id)))
		return (0);
	ft_list_push_back(&(env->head_champs), champ, sizeof(t_champ));
	free(champ);
	return (1);
}

int			get_champions(t_env *env, int argc, char **argv)
{
	int		i;
	int		fd;
	char	*extension;

	i = 0;
	extension = 0;
	while (++i < argc)
	{
		if (ft_strlen(argv[i]) > 4
			&& (extension = ft_strsub(argv[i], ft_strlen(argv[i]) - 4, 4))
			&& ft_strequ(extension, ".cor"))
		{
			ft_strdel(&extension);
			if ((fd = open(argv[i], O_RDONLY)) <= -1)
			{
				ft_putendl_fd("Invalid file.", 2);
				return (0);
			}
			if (!(ft_valid_champ(env, argv, i, fd)))
				return (0);
		}
		if (extension)
			ft_strdel(&extension);
	}
	return (env->nb_champs == 0 ? 0 : 1);
}
