/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:37:52 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 10:37:53 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static unsigned int		get_params1(t_arena *arena, t_process *process,
						int *add_to_pc, t_params params)
{
	int		pos;

	if (params.param1 == REG_CODE)
	{
		pos = process->pos + process->pc + *add_to_pc + MEM_SIZE;
		*add_to_pc += 1;
		return (process->reg[arena->cell[(pos) % MEM_SIZE].content - 1]);
	}
	else if (params.param1 == IND_CODE)
		return (get_ind_value(arena, process, add_to_pc));
	else if (params.param1 == DIR_CODE)
		return (get_dir_value(arena, process, add_to_pc));
	return (0);
}

static unsigned int		get_params2(t_arena *arena, t_process *process,
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
		return (get_dir_value(arena, process, add_to_pc));
	return (0);
}

static int				check_register(t_arena *arena, t_process *process,
						int add_to_pc, t_params params)
{
	int		pos;
	int		reg_number;

	pos = process->pos + process->pc + add_to_pc + MEM_SIZE;
	reg_number = arena->cell[(pos) % MEM_SIZE].content;
	if (!(reg_number >= 1 && reg_number <= REG_NUMBER))
	{
		process->pc += params_length(params, 8);
		return (0);
	}
	return (1);
}

static void				store_result(unsigned int value, t_process *process,
						unsigned int cell_content, int *add_to_pc)
{
	process->reg[cell_content - 1] = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
	*add_to_pc += 1;
	process->pc += *add_to_pc;
}

void					exec_xor(t_arena *arena, t_process *process)
{
	t_params		params;
	int				add_to_pc;
	unsigned int	param1_value;
	unsigned int	param2_value;
	int				pos;

	pos = process->pos + process->pc + MEM_SIZE;
	params = *(t_params*)&(arena->cell[(pos + 1) % MEM_SIZE].content);
	add_to_pc = 2;
	if (!valid_params(params, 8) || (params.param1 == REG_CODE &&
		!check_register(arena, process, add_to_pc, params)))
	{
		process->pc += !valid_params(params, 8) ? params_length(params, 8) : 0;
		return ;
	}
	param1_value = get_params1(arena, process, &add_to_pc, params);
	if (params.param2 == REG_CODE &&
		!check_register(arena, process, add_to_pc, params))
		return ;
	param2_value = get_params2(arena, process, &add_to_pc, params);
	if (!check_register(arena, process, add_to_pc, params))
		return ;
	store_result(param1_value ^ param2_value, process,
		arena->cell[(pos + add_to_pc) % MEM_SIZE].content, &add_to_pc);
}
