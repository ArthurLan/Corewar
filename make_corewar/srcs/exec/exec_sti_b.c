/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sti_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:24:29 by alanter           #+#    #+#             */
/*   Updated: 2018/12/06 14:24:31 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int						ft_check(t_arena *arena, t_process *process,
							t_params *params, int *add_to_pc)
{
	if (!valid_params(*params, 11) ||
		!ft_check_register(arena, process, *add_to_pc, *params))
	{
		process->pc += !valid_params(*params, 11) ?
			params_length(*params, 11) : 0;
		return (0);
	}
	return (1);
}
