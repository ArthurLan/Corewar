/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:51:50 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 14:51:52 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_live(t_env *env, t_arena *arena, t_process *process)
{
	unsigned int	champ_id;
	t_champ			*champ;
	unsigned int	pos;

	process->nb_live++;
	arena->nb_lives++;
	pos = process->pos + process->pc + MEM_SIZE;
	champ_id = (((arena->cell[(pos + 1) % MEM_SIZE].content) << 24) |
			(arena->cell[(pos + 2) % MEM_SIZE].content << 16) |
			(arena->cell[(pos + 3) % MEM_SIZE].content << 8) |
			(arena->cell[(pos + 4) % MEM_SIZE].content));
	if ((champ = find_champ(env, champ_id)))
	{
		champ->nb_live++;
		arena->last_live_champ_id = champ_id;
		if (env->opt.show_lives)
			ft_printf("A process say that %d(%s) is alive.\n",
			-champ_id, champ->header->prog_name);
	}
	process->pc += 1 + 4;
}
