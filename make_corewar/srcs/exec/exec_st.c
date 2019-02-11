/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:19:43 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 17:19:44 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		param2_index(t_arena *arena, t_process *process,
					int *add_to_pc, unsigned int reg_value)
{
	int		idxmod;
	int		pos;
	int		address;
	int		addmod;

	pos = process->pos + process->pc + MEM_SIZE;
	*add_to_pc += 1 + 2;
	address = (short)((arena->cell[(pos + 3) % MEM_SIZE].content) << 8) |
		(arena->cell[(pos + 4) % MEM_SIZE].content);
	idxmod = (address >= 0 ? IDX_MOD : -IDX_MOD);
	addmod = address % idxmod;
	arena->cell[(pos + addmod) % MEM_SIZE].color = process->color;
	arena->cell[(pos + addmod + 1) % MEM_SIZE].color = process->color;
	arena->cell[(pos + addmod + 2) % MEM_SIZE].color = process->color;
	arena->cell[(pos + addmod + 3) % MEM_SIZE].color = process->color;
	arena->cell[(pos + addmod) % MEM_SIZE].content = reg_value >> 24;
	arena->cell[(pos + addmod + 1) % MEM_SIZE].content = reg_value << 8 >> 24;
	arena->cell[(pos + addmod + 2) % MEM_SIZE].content = reg_value << 16 >> 24;
	arena->cell[(pos + addmod + 3) % MEM_SIZE].content = reg_value << 24 >> 24;
}

static int		param2_reg(t_arena *arena, t_process *process,
					int *add_to_pc, unsigned int reg_value)
{
	unsigned int	reg;

	*add_to_pc += 1 + 1;
	reg = arena->cell[(process->pos + process->pc
		+ 3 + MEM_SIZE) % MEM_SIZE].content;
	if (!(reg >= 1 && reg <= REG_NUMBER))
		return (0);
	process->reg[reg - 1] = reg_value;
	return (1);
}

void			exec_st(t_arena *arena, t_process *process)
{
	t_params		params;
	int				add_to_pc;
	unsigned int	reg;
	unsigned int	reg_value;

	add_to_pc = 2;
	params = *(t_params*)&(arena->cell[(process->pos +
		process->pc + 1 + MEM_SIZE) % MEM_SIZE].content);
	reg = arena->cell[(process->pos + process->pc
		+ 2 + MEM_SIZE) % MEM_SIZE].content;
	if ((!(valid_params(params, 3))) || reg <= 0 || reg > 16)
	{
		process->pc += params_length(params, 3);
		return ;
	}
	reg_value = process->reg[reg - 1];
	if (params.param2 == IND_CODE)
		param2_index(arena, process, &add_to_pc, reg_value);
	else if (params.param2 == REG_CODE
		&& !param2_reg(arena, process, &add_to_pc, reg_value))
	{
		process->pc += params_length(params, 3);
		return ;
	}
	process->pc += add_to_pc;
}
