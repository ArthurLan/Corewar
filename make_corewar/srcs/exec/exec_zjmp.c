/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:49:22 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 12:49:23 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_zjmp(t_arena *arena, t_process *process)
{
	int		add_to_pc;
	int		address;
	int		idxmod;

	add_to_pc = 1 + 2;
	if (process->carry == 1)
	{
		address = (short)
			(((arena->cell[(process->pos + process->pc
			+ 1 + MEM_SIZE) % MEM_SIZE].content) << 8) |
			arena->cell[(process->pos + process->pc
			+ 2 + MEM_SIZE) % MEM_SIZE].content);
		idxmod = address >= 0 ? IDX_MOD : -IDX_MOD;
		process->pc += (address % idxmod);
	}
	else
		process->pc += add_to_pc;
}
