/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:59:30 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 12:59:40 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int						ft_check_register(t_arena *arena, t_process *process,
						int add_to_pc, t_params params)
{
	int		pos;
	int		reg_number;

	pos = process->pos + process->pc + add_to_pc + MEM_SIZE;
	reg_number = arena->cell[(pos) % MEM_SIZE].content;
	if (!(reg_number >= 1 && reg_number <= REG_NUMBER))
	{
		process->pc += params_length(params, 11);
		return (0);
	}
	return (1);
}

static unsigned int		get_param2(t_arena *arena, t_process *process,
						int *add_to_pc, t_params params)
{
	int		pos;

	if (params.param2 == REG_CODE)
	{
		pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
		*add_to_pc += 1;
		return (process->reg[arena->cell[(pos) % MEM_SIZE].content - 1]);
	}
	else if (params.param2 == IND_CODE)
		return (get_ind_value(arena, process, add_to_pc));
	else if (params.param2 == DIR_CODE)
	{
		pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
		*add_to_pc += 2;
		return (((arena->cell[(pos) % MEM_SIZE].content) << 8) |
			(arena->cell[(pos + 1) % MEM_SIZE].content));
	}
	return (0);
}

static unsigned int		get_param3(t_arena *arena, t_process *process,
						int *add_to_pc, t_params params)
{
	int			pos;

	if (params.param3 == DIR_CODE)
	{
		pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
		*add_to_pc += 2;
		return (((arena->cell[(pos) % MEM_SIZE].content) << 8) |
			(arena->cell[(pos + 1) % MEM_SIZE].content));
	}
	else if (params.param3 == REG_CODE)
	{
		pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
		*add_to_pc += 1;
		return (process->reg[arena->cell[(pos) % MEM_SIZE].content - 1]);
	}
	return (0);
}

void					store_result_to_ram(t_arena *arena, t_process *process,
							unsigned int param1_value, short address)
{
	int				idxmod;
	int				pos;

	idxmod = (address >= 0 ? IDX_MOD : -IDX_MOD);
	address %= idxmod;
	pos = process->pos + process->pc + address + MEM_SIZE;
	arena->cell[(pos) % MEM_SIZE].color = process->color;
	arena->cell[(pos + 1) % MEM_SIZE].color = process->color;
	arena->cell[(pos + 2) % MEM_SIZE].color = process->color;
	arena->cell[(pos + 3) % MEM_SIZE].color = process->color;
	arena->cell[(pos) % MEM_SIZE].content = param1_value >> 24;
	arena->cell[(pos + 1) % MEM_SIZE].content = param1_value << 8 >> 24;
	arena->cell[(pos + 2) % MEM_SIZE].content = param1_value << 16 >> 24;
	arena->cell[(pos + 3) % MEM_SIZE].content = param1_value << 24 >> 24;
}

void					exec_sti(t_arena *arena, t_process *process)
{
	int				add_to_pc;
	t_params		params;
	unsigned int	param1_value;
	unsigned int	param2_value;
	unsigned int	param3_value;

	add_to_pc = 1 + 1;
	params = *(t_params*)&(arena->cell[(process->pos +
		process->pc + 1 + MEM_SIZE) % MEM_SIZE].content);
	if (!ft_check(arena, process, &params, &add_to_pc))
		return ;
	param1_value = process->reg[arena->cell[(process->pos + process->pc
		+ add_to_pc + MEM_SIZE) % MEM_SIZE].content - 1];
	add_to_pc += 1;
	if (params.param2 == REG_CODE &&
		!ft_check_register(arena, process, add_to_pc, params))
		return ;
	param2_value = get_param2(arena, process, &add_to_pc, params);
	if (params.param3 == REG_CODE &&
		!ft_check_register(arena, process, add_to_pc, params))
		return ;
	param3_value = get_param3(arena, process, &add_to_pc, params);
	store_result_to_ram(arena, process, param1_value,
		(short)(param2_value + param3_value));
	process->pc += add_to_pc;
}
