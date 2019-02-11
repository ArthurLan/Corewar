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

static void		ft_color(void)
{
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(22, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(32, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(42, COLOR_YELLOW, COLOR_WHITE);
	init_pair(8, COLOR_CYAN, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_WHITE);
}

static WINDOW	**ft_box(WINDOW *stdscr)
{
	WINDOW **winlst;
	WINDOW *left;
	WINDOW *right;
	WINDOW *title;

	if (!(winlst = (WINDOW**)ft_memalloc(sizeof(WINDOW*) * 3)))
		return (NULL);
	resizeterm(72, 250);
	title = subwin(stdscr, 4, 100, 0, 50);
	left = subwin(stdscr, 71, 199, 0, 0);
	right = subwin(stdscr, 71, 50, 0, 199);
	winlst[0] = title;
	winlst[1] = left;
	winlst[2] = right;
	wattron(left, COLOR_PAIR(9));
	wattron(right, COLOR_PAIR(9));
	wattron(title, COLOR_PAIR(9));
	box(left, ACS_VLINE, ACS_HLINE);
	box(right, ACS_VLINE, ACS_HLINE);
	box(title, ACS_VLINE, ACS_HLINE);
	wattroff(title, COLOR_PAIR(9));
	wattroff(left, COLOR_PAIR(9));
	wattroff(right, COLOR_PAIR(9));
	return (winlst);
}

static void		ft_key(WINDOW *stdscr, t_arena *arena)
{
	int key;
	int playpau;

	playpau = 0;
	nodelay(stdscr, true);
	key = getch();
	if (key == 32)
		playpau = (playpau == 1) ? 0 : 1;
	while (playpau)
	{
		key = getch();
		if (key == 32)
			playpau = (playpau == 1) ? 0 : 1;
		else if (key == 27)
			ft_exit();
	}
	if (key == 27)
		ft_exit();
	if (key == 48)
		arena->visual.time = 999999;
	arena->visual.time = (key > 48 && key < 58) ? (key - 48) * (key - 48) *
		(key - 48) * (key - 48) * (key - 48) * 5 : arena->visual.time;
}

static void		ft_nbr(t_cell *cell, int cell_nbr, int j, int k)
{
	int i;

	while (++j < 64 && (i = -1))
	{
		while (++i < 64 && (++cell_nbr) != -1)
		{
			if (cell[cell_nbr].color == 1)
				attron(cell[cell_nbr].active ? COLOR_PAIR(12) : COLOR_PAIR(1));
			else if (cell[cell_nbr].color == 2)
				attron(cell[cell_nbr].active ? COLOR_PAIR(22) : COLOR_PAIR(2));
			else if (cell[cell_nbr].color == 3)
				attron(cell[cell_nbr].active ? COLOR_PAIR(32) : COLOR_PAIR(3));
			else if (cell[cell_nbr].color == 4)
				attron(cell[cell_nbr].active ? COLOR_PAIR(42) : COLOR_PAIR(4));
			else if (cell[cell_nbr].color == 8)
				attron(COLOR_PAIR(8));
			mvprintw(j + 5, (k % 192) + 4, "%02x", cell[cell_nbr].content);
			attroff(cell[cell_nbr].active ? COLOR_PAIR(12) : COLOR_PAIR(1));
			attroff(cell[cell_nbr].active ? COLOR_PAIR(22) : COLOR_PAIR(2));
			attroff(cell[cell_nbr].active ? COLOR_PAIR(32) : COLOR_PAIR(3));
			attroff(cell[cell_nbr].active ? COLOR_PAIR(42) : COLOR_PAIR(4));
			attroff(COLOR_PAIR(8));
			k += 3;
		}
	}
}

int				display_ncurses(t_cell *cell, t_env *env)
{
	static WINDOW	**winlst = NULL;

	if (env->arena->nb_process <= -1 || env->arena->cycles_to_die <= 0)
	{
		ft_winner(env);
		while (1)
		{
			if (getch() == 27)
				ft_exit();
		}
	}
	initscr();
	if (winlst == NULL)
		winlst = ft_box(stdscr);
	ft_color();
	ft_key(stdscr, env->arena);
	ft_text(stdscr, env);
	ft_nbr(cell, -1, -1, 0);
	refresh();
	wrefresh(winlst[1]);
	wrefresh(winlst[2]);
	return (0);
}
