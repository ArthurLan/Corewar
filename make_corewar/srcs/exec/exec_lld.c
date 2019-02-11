/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:31:31 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 16:31:32 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	 2 octets a prendre
**	 val % MEM_SIZE
**	 on ajoute 2 au pc pour le IND et 1 pour le reg
**	 On lit les 2 octets que l'on caste en short,
**	 et on prend la valeur de cette case
*/

static void		ft_carry(t_process *process, unsigned int cell_value)
{
	if (cell_value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

static int		ft_ind_code(t_arena *arena, t_process *process,
					int *add_to_pc, t_params params)
{
	int				address;
	unsigned int	cell_value;
	unsigned int	reg;
	int				pos;

	pos = process->pos + process->pc + MEM_SIZE;
	*add_to_pc += 2 + 1;
	address = (short)(((arena->cell[(pos + 2) % MEM_SIZE].content) << 8) |
		arena->cell[(pos + 3) % MEM_SIZE].content);
	reg = arena->cell[(pos + 4) % MEM_SIZE].content;
	cell_value = (arena->cell[(pos + address)
			% MEM_SIZE].content << 24) |
		(arena->cell[(pos + address + 1) % MEM_SIZE].content << 16) |
		(arena->cell[(pos + address + 2) % MEM_SIZE].content << 8) |
		(arena->cell[(pos + address + 3) % MEM_SIZE].content);
	if (reg <= 0 || reg > REG_NUMBER)
	{
		process->pc += params_length(params, 13);
		return (1);
	}
	process->reg[reg - 1] = cell_value;
	ft_carry(process, cell_value);
	return (0);
}

/*
**	 4 octets a prendre
**	 On lit les 4 octets, et on va chercher la case
*/

static int		ft_d_code(t_arena *arena, t_process *process,
					int *add_to_pc, t_params params)
{
	unsigned int	cell_value;
	unsigned int	reg;
	int				pos;

	*add_to_pc += 4 + 1;
	pos = process->pos + process->pc + MEM_SIZE;
	cell_value = (((arena->cell[(pos + 2) % MEM_SIZE].content) << 24) |
		(arena->cell[(pos + 3) % MEM_SIZE].content << 16) |
		(arena->cell[(pos + 4) % MEM_SIZE].content << 8) |
		(arena->cell[(pos + 5) % MEM_SIZE].content));
	reg = arena->cell[(pos + 6) % MEM_SIZE].content;
	if (reg <= 0 || reg > REG_NUMBER)
	{
		process->pc += params_length(params, 2);
		return (1);
	}
	process->reg[reg - 1] = cell_value;
	ft_carry(process, cell_value);
	return (0);
}

void			exec_lld(t_arena *arena, t_process *process)
{
	t_params		params;
	int				add_to_pc;

	add_to_pc = 2;
	params = *(t_params*)&(arena->cell[(process->pos + process->pc
			+ 1 + MEM_SIZE) % MEM_SIZE].content);
	if (!valid_params(params, 13))
	{
		process->pc += params_length(params, 13);
		return ;
	}
	if (params.param1 == IND_CODE &&
		ft_ind_code(arena, process, &add_to_pc, params))
		return ;
	else if (params.param1 == DIR_CODE &&
		ft_d_code(arena, process, &add_to_pc, params))
		return ;
	else if (params.param1 != IND_CODE && params.param1 != DIR_CODE)
	{
		process->pc++;
		return ;
	}
	process->pc += add_to_pc;
}
