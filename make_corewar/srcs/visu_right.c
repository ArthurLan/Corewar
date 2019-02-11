/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 23:09:18 by alanter           #+#    #+#             */
/*   Updated: 2018/11/29 23:09:20 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_champion(t_list **head)
{
	t_list	*list;
	t_champ *champ;
	int		i;

	i = 0;
	list = *head;
	while (list)
	{
		attron(COLOR_PAIR(i + 1));
		champ = (t_champ*)list->content;
		mvprintw(9 + i, 203, "%s(%d) reported alive %d times.",
			champ->header->prog_name, -champ->id, champ->nb_live);
		attroff(COLOR_PAIR(i + 1));
		i++;
		list = list->next;
	}
}

void	ft_menu(void)
{
	mvprintw(56, 203, "Speed :");
	mvprintw(57, 205, "1 : 5µs");
	mvprintw(58, 205, "2 : 150µs");
	mvprintw(59, 205, "3 : 1ms");
	mvprintw(60, 205, "4 : 5ms");
	mvprintw(61, 205, "5 : 15ms");
	mvprintw(62, 205, "6 : 38ms");
	mvprintw(63, 205, "7 : 84ms");
	mvprintw(64, 205, "8 : 163ms");
	mvprintw(65, 205, "9 : 295ms");
	mvprintw(66, 205, "0 : 1s");
	mvprintw(67, 203, "Space : pause.");
	mvprintw(68, 203, "Esc : escape.");
	mvprintw(68, 195, "   ");
}

void	ft_text(WINDOW *stdscr, t_env *env)
{
	static int cycle_nbr = 0;

	mvprintw(1, 95, "~~~ COREWAR ~~~");
	attron(COLOR_PAIR(1));
	mvprintw(2, 83, "ncohen, ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	printw("mdaunois, ");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	printw("clecalie, ");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(4));
	printw("alanter");
	attroff(COLOR_PAIR(4));
	mvprintw(5, 203, "Cycle : %d", cycle_nbr);
	mvprintw(6, 203, "                             ");
	mvprintw(6, 203, "Time : %dms", (env->arena->visual.time + 1) / 1000);
	mvprintw(7, 203, "Process : %d", env->arena->nb_process);
	if (env->arena->cycles_to_die < 1000)
		mvprintw(8, 203, "CYCLE_TO_DIE :           ");
	mvprintw(8, 203, "CYCLE_TO_DIE : %d", env->arena->cycles_to_die);
	ft_menu();
	ft_champion(&(env->head_champs));
	cycle_nbr++;
}

void	ft_exit(void)
{
	clear();
	endwin();
	refresh();
	endwin();
	exit(1);
}

void	ft_winner(t_env *env)
{
	char *winner;
	char *nbr;

	nbr = ft_itoa(env->arena->last_live_champ_id);
	winner = ft_strjoin("Say the winner is", nbr);
	free(nbr);
	mvprintw(20, 203, "Battle ended after %d cycles!", env->arena->cycles);
	mvprintw(21, 203, "The winner is the player %d(%s)\n",
		-env->arena->last_live_champ_id,
		find_champ(env, env->arena->last_live_champ_id)->header->prog_name);
	system(winner);
	free(winner);
}
