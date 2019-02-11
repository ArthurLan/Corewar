/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:01:13 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 16:01:15 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_aff(t_arena *arena, t_process *process)
{
	t_params		params;
	unsigned int	reg;
	unsigned int	reg_value;
	int				pos;

	pos = process->pos + process->pc + MEM_SIZE;
	params = *(t_params*)&(arena->cell[(pos + 1) % MEM_SIZE].content);
	reg = arena->cell[(pos + 2) % MEM_SIZE].content;
	if ((!(valid_params(params, 16))) || reg <= 0 || reg > 16)
	{
		process->pc += params_length(params, 16);
		return ;
	}
	reg_value = process->reg[reg - 1];
	arena->visual.aff = reg_value % 256;
	process->pc += 3;
}
