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

unsigned int	get_champ_size(unsigned char *src)
{
	unsigned int	size;

	size = src[0] << 8;
	size += src[1] << 8;
	size += src[2] << 8;
	size += src[3];
	return (size);
}

void			ft_exec_magic(unsigned char *temp)
{
	if (temp[0] != 0
		|| (COREWAR_EXEC_MAGIC >> 16) != temp[1]
		|| (COREWAR_EXEC_MAGIC >> 8 & 0xFF) != temp[2]
		|| (COREWAR_EXEC_MAGIC & 0xFF) != temp[3])
	{
		ft_putendl_fd("Error: Invalid corewar exec magic.", 2);
		exit(0);
	}
}

void			ft_prog_name(t_header *header,
					unsigned char *buff, int *i, int *j)
{
	*i = 4;
	*j = 0;
	while (*j < PROG_NAME_LENGTH)
	{
		header->prog_name[*j] = buff[*i];
		*i += 1;
		*j += 1;
	}
	*i += PADDING_SIZE;
}

void			ft_comment(t_header *header,
					unsigned char *buff, int *i, int *j)
{
	*i += INSTRUCTION_SIZE;
	*j = 0;
	while (*j < COMMENT_LENGTH)
	{
		header->comment[*j] = buff[*i];
		*i += 1;
		*j += 1;
	}
}

t_header		*parse_header(unsigned char *buff)
{
	t_header		*header;
	int				i;
	int				j;
	unsigned char	*temp;

	if (!(header = (t_header*)malloc(sizeof(t_header))))
		return (0);
	temp = ft_ustrsub(buff, 0, 4);
	ft_exec_magic(temp);
	header->magic = COREWAR_EXEC_MAGIC;
	free(temp);
	ft_prog_name(header, buff, &i, &j);
	temp = ft_ustrsub(buff, i, 4);
	header->prog_size = get_champ_size(temp);
	if (header->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("Size of champion %s is superior than %d bytes.",
			header->prog_name, CHAMP_MAX_SIZE);
		exit(0);
	}
	free(temp);
	ft_comment(header, buff, &i, &j);
	return (header);
}
