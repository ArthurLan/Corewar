/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:37:12 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 16:37:13 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int	get_param1(t_arena *arena, t_process *process,
					int param, int *add_to_pc)
{
	int		pos;

	pos = process->pos + process->pc + MEM_SIZE;
	if (param == REG_CODE)
	{
		pos += *add_to_pc;
		*add_to_pc += 1;
		return (process->reg[arena->cell[(pos) % MEM_SIZE].content - 1]);
	}
	else if (param == IND_CODE)
		return (get_long_ind_value(arena, process, add_to_pc));
	else if (param == DIR_CODE)
	{
		pos += *add_to_pc;
		*add_to_pc += 2;
		return (((arena->cell[(pos) % MEM_SIZE].content) << 8) |
			(arena->cell[(pos + 1) % MEM_SIZE].content));
	}
	else
		return (0);
}

static unsigned int	get_param2(t_arena *arena, t_process *process,
					int param, int *add_to_pc)
{
	int		pos;

	pos = process->pos + process->pc + MEM_SIZE;
	if (param == REG_CODE)
	{
		pos += *add_to_pc;
		*add_to_pc += 1;
		return (process->reg[arena->cell[(pos) % MEM_SIZE].content - 1]);
	}
	else if (param == DIR_CODE)
	{
		pos += *add_to_pc;
		*add_to_pc += 2;
		return (((arena->cell[(pos) % MEM_SIZE].content) << 8) |
			(arena->cell[(pos + 1) % MEM_SIZE].content));
	}
	else
		return (0);
}

static unsigned int	get_address_value(t_arena *arena, t_process *process,
					short address)
{
	int		pos;

	pos = process->pos + process->pc + MEM_SIZE;
	return (
	(arena->cell[(pos + (address)) % MEM_SIZE].content << 24) |
	(arena->cell[(pos + ((address + 1))) % MEM_SIZE].content << 16) |
	(arena->cell[(pos + ((address + 2))) % MEM_SIZE].content << 8) |
	(arena->cell[(pos + ((address + 3))) % MEM_SIZE].content));
}

void				exec_lldi(t_arena *arena, t_process *process)
{
	int				add_to_pc;
	t_params		params;
	unsigned int	param1_value;
	unsigned int	param2_value;

	add_to_pc = 1 + 1;
	params = *(t_params*)&(arena->cell[(process->pos + process->pc
		+ 1 + MEM_SIZE) % MEM_SIZE].content);
	if (!valid_params(params, 14))
	{
		process->pc += params_length(params, 14);
		return ;
	}
	param1_value = get_param1(arena, process, params.param1, &add_to_pc);
	param2_value = get_param2(arena, process, params.param2, &add_to_pc);
	process->reg[arena->cell[(process->pos + process->pc + add_to_pc +
		MEM_SIZE) % MEM_SIZE].content - 1] = get_address_value(arena, process,
		param1_value + param2_value);
	if (param1_value + param2_value == 0)
		process->carry = 1;
	else
		process->carry = 0;
	add_to_pc += 1;
	process->pc += add_to_pc;
}
