/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:11:02 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/23 13:11:03 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	find_op(unsigned char op)
{
	int		i;
	t_op	current_op;

	i = 0;
	while (i <= 16)
	{
		if (g_op_tab[i].id == op)
		{
			current_op = g_op_tab[i];
			return (current_op);
		}
		i++;
	}
	return (g_op_tab[16]);
}

int		valid_params(t_params params, int opcode)
{
	t_op	op;
	int		nb_params;

	op = find_op(opcode);
	if (op.id == 0)
		return (1);
	nb_params = op.nb_params;
	if (params.param1 == 0 || ((params.param1 == IND_CODE ?
		T_IND : params.param1) | op.params_type[0]) != op.params_type[0])
		return (0);
	if (nb_params >= 2 && (params.param2 == 0 || ((params.param2 == IND_CODE ?
		T_IND : params.param2) | op.params_type[1]) != op.params_type[1]))
		return (0);
	if (nb_params == 3 && (params.param3 == 0 || ((params.param3 == IND_CODE ?
		T_IND : params.param3) | op.params_type[2]) != op.params_type[2]))
		return (0);
	return (1);
}

void	ft_jump(int *jump, t_op op, int i)
{
	if (i == 1)
		*jump += 1;
	else if (i == 2)
		*jump += op.dir_size == 0 ? 4 : 2;
	else if (i == 3)
		*jump += 2;
}

int		params_length(t_params params, int opcode)
{
	int		jump;
	t_op	op;
	int		nb_params;

	op = find_op(opcode);
	if (op.id == 0)
		return (1);
	nb_params = op.nb_params;
	jump = 1 + 1;
	if (ft_strequ(op.name, "live") || ft_strequ(op.name, "zjmp")
		|| ft_strequ(op.name, "fork") || ft_strequ(op.name, "lfork"))
		jump--;
	ft_jump(&jump, op, params.param1);
	if (nb_params >= 2)
		ft_jump(&jump, op, params.param2);
	if (nb_params == 3)
		ft_jump(&jump, op, params.param3);
	return (jump);
}

void	exec_op(t_env *env, t_arena *arena, t_process *proc, unsigned char op)
{
	void	(*ptr[17])(t_arena *arena, t_process *proc);

	proc->last_op = 0;
	proc->last_op_cycle_end = 0;
	arena->cell[(proc->pos + proc->pc + MEM_SIZE) % MEM_SIZE].active = 0;
	ptr[2] = exec_ld;
	ptr[3] = exec_st;
	ptr[4] = exec_add;
	ptr[5] = exec_sub;
	ptr[6] = exec_and;
	ptr[7] = exec_or;
	ptr[8] = exec_xor;
	ptr[9] = exec_zjmp;
	ptr[10] = exec_ldi;
	ptr[11] = exec_sti;
	ptr[12] = exec_fork;
	ptr[13] = exec_lld;
	ptr[14] = exec_lldi;
	ptr[15] = exec_lfork;
	ptr[16] = exec_aff;
	return (op == 1 ? exec_live(env, arena, proc) : (*ptr[op])(arena, proc));
}
