/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:54:51 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/22 15:54:52 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_cycles(t_env *env, t_arena *arena)
{
	if (arena->cycles != 0 && (int)arena->cycles == arena->next_check)
	{
		ft_list_remove_nb_cycle_0(arena);
		reset_champ_lives(&(env->head_champs));
		if (arena->nb_lives >= NBR_LIVE)
		{
			arena->cycles_to_die -= CYCLE_DELTA;
			arena->verif = 0;
		}
		else
		{
			if (arena->verif == MAX_CHECKS)
			{
				arena->cycles_to_die -= CYCLE_DELTA;
				arena->verif = 0;
			}
			else
				arena->verif++;
		}
		arena->nb_lives = 0;
		arena->next_check = arena->cycles + arena->cycles_to_die;
	}
}

int		is_end_of_game(t_env *env)
{
	t_arena *arena;

	arena = env->arena;
	if (env->opt.visu == 0 &&
		(arena->nb_process <= 0 || arena->cycles_to_die <= 0))
	{
		delete_temp_process(&(arena->process));
		delete_temp_process(&(arena->temp_process));
		ft_printf("The battle end after %d cycles. ", arena->cycles);
		ft_printf("The winner is the player %d(%s)\n",
		-arena->last_live_champ_id,
		find_champ(env, arena->last_live_champ_id)->header->prog_name);
		return (1);
	}
	if (env->opt.is_dump_set && env->opt.dump_value == (int)arena->cycles)
	{
		delete_temp_process(&(arena->process));
		delete_temp_process(&(arena->temp_process));
		display_arena(arena->cell);
		return (1);
	}
	return (0);
}

void	init_op(t_arena *arena, t_process *process)
{
	unsigned char	op;

	op = arena->cell[(process->pos + process->pc) % MEM_SIZE].content;
	if (find_op(op).id != 0)
	{
		arena->cell[(process->pos + process->pc) % MEM_SIZE].active = 1;
		process->last_op = op;
		process->last_op_cycle_end = arena->cycles + find_op(op).cycles - 1;
	}
	else
	{
		process->pc++;
		if (arena->cell[(process->pos + process->pc) % MEM_SIZE].color == 37)
			arena->cell[(process->pos + process->pc) % MEM_SIZE].color = 8;
	}
}

void	check_for_running_op(t_env *env, t_process *process)
{
	t_arena		*arena;

	arena = env->arena;
	if (arena->cell[(process->pos + process->pc) % MEM_SIZE].color == 8
		&& find_op(arena->cell[(process->pos
		+ process->pc) % MEM_SIZE].content).id == 0)
		arena->cell[(process->pos + process->pc) % MEM_SIZE].color = 37;
	if (process->last_op_cycle_end <= arena->cycles)
	{
		if (process->last_op != 0)
			exec_op(env, arena, process, process->last_op);
		else
			init_op(arena, process);
	}
}

void	run_cycle(t_env *env)
{
	t_list			*process_list;
	t_process		*process;
	t_arena			*arena;

	arena = env->arena;
	check_cycles(env, arena);
	if (is_end_of_game(env))
		return ;
	process_list = arena->process;
	while (process_list)
	{
		process = (t_process*)(process_list->content);
		check_for_running_op(env, process);
		process_list = process_list->next;
	}
	add_temp_process(arena);
	arena->cycles++;
	if (env->opt.visu == 1)
		display_arena_ncurses(env, arena);
	run_cycle(env);
}
