/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:59:05 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/22 13:59:05 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	display_arena_ncurses(t_env *env, t_arena *arena)
{
	if (!env->opt.is_dump_set)
	{
		usleep(arena->visual.time);
		display_ncurses(arena->cell, env);
	}
}

void	display_arena(t_cell *cell)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", (unsigned char)(cell[i].content));
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		i++;
	}
}

void	ft_init(t_env *env)
{
	env->arena->process = 0;
	env->arena->next_check = CYCLE_TO_DIE;
	env->arena->last_process_id = 1;
	env->arena->cycles = 0;
	env->arena->cycles_to_die = CYCLE_TO_DIE;
	env->arena->nb_lives = 0;
	env->arena->nb_process = 0;
	env->arena->last_live_champ_id = -1;
	env->arena->verif = 0;
	env->arena->temp_process = 0;
}

void	ft_init_process(t_env *env, t_list *champ_list,
			unsigned int size_per_champion)
{
	static unsigned int	i = 0;
	unsigned int		j;
	t_champ				*current_champ;
	t_process			*process;

	current_champ = (t_champ*)champ_list->content;
	j = 0;
	if (!(process = init_process(i, current_champ,
		env->arena->last_process_id++)))
		exit(1);
	env->arena->nb_process++;
	ft_list_push_front(&(env->arena->process), process, sizeof(t_process));
	free(process);
	while (j < size_per_champion + (MEM_SIZE % size_per_champion)
		&& i < MEM_SIZE)
	{
		env->arena->cell[i].content = j < current_champ->header->prog_size ?
			(unsigned char)current_champ->content[j] : 0;
		env->arena->cell[i].color = j < current_champ->header->prog_size ?
			current_champ->color : GREY_COLOR;
		env->arena->cell[i].active = 0;
		i++;
		j++;
	}
}

void	init_arena(t_env *env)
{
	t_list				*champ_list;
	unsigned int		size_per_champion;

	if (!(env->arena = (t_arena*)malloc(sizeof(t_arena))))
		exit(1);
	ft_init(env);
	if (!(env->arena->cell = (t_cell*)malloc((sizeof(t_cell) * MEM_SIZE) + 1)))
		exit(1);
	size_per_champion = MEM_SIZE / env->nb_champs;
	champ_list = env->head_champs;
	while (champ_list)
	{
		ft_init_process(env, champ_list, size_per_champion);
		champ_list = champ_list->next;
	}
	env->arena->visual.time = 20000;
}
