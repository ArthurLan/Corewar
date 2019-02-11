/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:48:09 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 12:48:10 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_fork(t_arena *arena, t_process *process)
{
	int				add_to_pc;
	int				idxmod;
	unsigned int	new_pc;
	int				direct;
	t_process		*new_process;

	add_to_pc = 1;
	direct = (short)((
		(arena->cell[(process->pos + process->pc +
		add_to_pc + MEM_SIZE) % MEM_SIZE].content) << 8)
		| arena->cell[(process->pos + process->pc +
		add_to_pc + 1 + MEM_SIZE) % MEM_SIZE].content);
	idxmod = (direct >= 0 ? IDX_MOD : -IDX_MOD);
	new_pc = process->pc + (direct % idxmod);
	arena->nb_process++;
	new_process = dup_process(process, new_pc, arena->last_process_id++);
	ft_list_push_back(&(arena->temp_process), new_process, sizeof(t_process));
	free(new_process);
	add_to_pc += 2;
	process->pc += add_to_pc;
}
