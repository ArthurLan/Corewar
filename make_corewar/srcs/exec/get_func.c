/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:37:39 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 11:37:45 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	get_long_ind_value(t_arena *arena,
					t_process *process, int *add_to_pc)
{
	int		address;
	int		pos;

	pos = process->pos + process->pc + MEM_SIZE;
	address = (short)(((arena->cell[(pos + *add_to_pc)
		% MEM_SIZE].content) << 8) |
	arena->cell[(pos + *add_to_pc + 1) % MEM_SIZE].content);
	*add_to_pc += 2;
	return (
	(arena->cell[(pos + address) % MEM_SIZE].content << 24) |
	(arena->cell[(pos + (address + 1)) % MEM_SIZE].content << 16) |
	(arena->cell[(pos + (address + 2)) % MEM_SIZE].content << 8) |
	(arena->cell[(pos + (address + 3)) % MEM_SIZE].content));
}

unsigned int	get_ind_value(t_arena *arena,
					t_process *process, int *add_to_pc)
{
	int		address;
	int		idxmod;
	int		pos;

	pos = process->pos + process->pc + MEM_SIZE;
	address = (short)(((arena->cell[(pos + *add_to_pc)
		% MEM_SIZE].content) << 8) |
	arena->cell[(pos + *add_to_pc + 1) % MEM_SIZE].content);
	idxmod = (address >= 0 ? IDX_MOD : -IDX_MOD);
	*add_to_pc += 2;
	return (
	(arena->cell[(pos + (address % idxmod)) % MEM_SIZE].content << 24) |
	(arena->cell[(pos + ((address + 1) % idxmod)) % MEM_SIZE].content << 16) |
	(arena->cell[(pos + ((address + 2) % idxmod)) % MEM_SIZE].content << 8) |
	(arena->cell[(pos + ((address + 3) % idxmod)) % MEM_SIZE].content));
}

unsigned int	get_dir_value(t_arena *arena,
				t_process *process, int *add_to_pc)
{
	int		pos;

	pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
	*add_to_pc += 4;
	return (((arena->cell[(pos) % MEM_SIZE].content) << 24) |
			(arena->cell[(pos + 1) % MEM_SIZE].content << 16) |
			(arena->cell[(pos + 2) % MEM_SIZE].content << 8) |
			(arena->cell[(pos + 3) % MEM_SIZE].content));
}
