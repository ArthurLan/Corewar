/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:32:52 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/05 10:32:54 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_sub(t_arena *arena, t_process *process, t_params params)
{
	unsigned int	sub;
	unsigned int	reg_param1;
	unsigned int	reg_param2;
	int				pos;

	pos = process->pos + process->pc + MEM_SIZE;
	reg_param1 = arena->cell[(pos + 2) % MEM_SIZE].content;
	reg_param2 = arena->cell[(pos + 3) % MEM_SIZE].content;
	if (!(reg_param1 >= 1 && reg_param1 <= REG_NUMBER)
			|| !(reg_param2 >= 1 && reg_param2 <= REG_NUMBER))
	{
		process->pc += params_length(params, 5);
		return (1);
	}
	sub = process->reg[reg_param1 - 1] - process->reg[reg_param2 - 1];
	process->reg[arena->cell[(pos + 4) % MEM_SIZE].content - 1] = sub;
	if (sub == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (0);
}

void		exec_sub(t_arena *arena, t_process *process)
{
	t_params		params;
	int				add_to_pc;

	add_to_pc = 2 + 1 + 1 + 1;
	params = *(t_params*)&(arena->cell[(process->pos +
		process->pc + 1 + MEM_SIZE) % MEM_SIZE].content);
	if (!valid_params(params, 5))
	{
		process->pc += params_length(params, 5);
		return ;
	}
	if (params.param1 == REG_CODE && params.param2 == REG_CODE
		&& params.param3 == REG_CODE)
	{
		if (ft_sub(arena, process, params))
			return ;
	}
	process->pc += add_to_pc;
}
