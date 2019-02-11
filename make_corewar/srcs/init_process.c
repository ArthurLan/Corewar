/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 16:34:26 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/22 16:34:27 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*dup_process(t_process *process, unsigned int pc, int pid)
{
	t_process	*new_process;
	int			reg;

	if (!(new_process = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	new_process->pid = pid;
	new_process->pc = pc;
	new_process->carry = process->carry;
	new_process->last_op = 0;
	new_process->nb_live = process->nb_live;
	new_process->last_op_cycle_end = 0;
	new_process->pos = process->pos;
	new_process->champ_id = process->champ_id;
	new_process->color = process->color;
	reg = 0;
	while (reg < REG_NUMBER)
	{
		new_process->reg[reg] = process->reg[reg];
		reg++;
	}
	return (new_process);
}

t_process	*init_process(unsigned int pos, t_champ *champ, int pid)
{
	t_process	*new_process;
	int			i;

	if (!(new_process = (t_process*)malloc(sizeof(t_process))))
		exit(0);
	new_process->pid = pid;
	new_process->pc = 0;
	new_process->carry = 0;
	new_process->last_op = 0;
	new_process->nb_live = 0;
	new_process->last_op_cycle_end = 0;
	new_process->pos = pos;
	new_process->champ_id = champ->id;
	new_process->color = champ->color;
	new_process->reg[0] = champ->id;
	i = 0;
	while (++i < REG_NUMBER)
		new_process->reg[i] = 0;
	return (new_process);
}
