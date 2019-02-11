/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:02:41 by clecalie          #+#    #+#             */
/*   Updated: 2018/11/21 12:04:02 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_H
# define FT_COREWAR_H
# include <fcntl.h>
# include <ncurses.h>
# include <curses.h>
# include <ulimit.h>
# include "op.h"
# include "../../libft/includes/libft.h"
# define ABS(x) ((x)<0 ? -(x) : (x))
# define PADDING_SIZE 4
# define HEAD_SIZE 2192
# define INSTRUCTION_SIZE 4
# define GREY_COLOR 37

typedef struct		s_opt
{
	int		is_dump_set;
	int		dump_value;
	int		show_lives;
	int		visu;
}					t_opt;

typedef struct		s_champ
{
	t_header			*header;
	unsigned char		*content;
	unsigned int		color;
	unsigned int		id;
	unsigned int		nb_live;
	int					is_alive;
}					t_champ;

typedef struct		s_cell
{
	unsigned char	content;
	unsigned char	current_op;
	unsigned int	color;
	int				active;
}					t_cell;

typedef struct		s_process
{
	unsigned int	pid;
	unsigned int	pc;
	int				carry;
	unsigned int	pos;
	unsigned int	color;
	unsigned int	last_op;
	unsigned int	last_op_cycle_end;
	unsigned int	champ_id;
	int				nb_live;
	unsigned int	reg[REG_NUMBER];
}					t_process;

typedef struct		s_visual
{
	int				time;
	char			aff;
}					t_visual;

typedef struct		s_arena
{
	int				next_check;
	int				last_process_id;
	t_list			*process;
	t_list			*temp_process;
	int				nb_process;
	t_cell			*cell;
	unsigned int	cycles;
	int				cycles_to_die;
	unsigned int	nb_lives;
	unsigned int	last_live_champ_id;
	int				verif;
	t_visual		visual;
}					t_arena;

typedef struct		s_env
{
	t_opt			opt;
	int				nb_champs;
	t_list			*head_champs;
	t_arena			*arena;
}					t_env;

typedef struct		s_params
{
	unsigned char	vide : 2;
	unsigned char	param3 : 2;
	unsigned char	param2 : 2;
	unsigned char	param1 : 2;
}					t_params;

/*
**	Initialize
*/
unsigned char		*ft_ustrsub(unsigned char *s,
					unsigned int start, size_t len);
void				init_arena(t_env *env);
int					get_champions(t_env *env, int argc, char **argv);
t_header			*parse_header(unsigned char *buff);

/*
**	Battle
*/
void				run_cycle(t_env *env);
void				display_arena(t_cell *cell);
t_op				find_op(unsigned char op);
void				exec_op(t_env *env, t_arena *arena,
					t_process *process, unsigned char op);

/*
**	Champions
*/
void				reset_champ_lives(t_list **head);
int					champ_alive(t_env *env);
t_champ				*find_champ(t_env *env, unsigned int champ_id);

/*
**	Processes
*/
t_process			*init_process(unsigned int pos, t_champ *champ, int pid);
t_process			*dup_process(t_process *process, unsigned int pc, int pid);
void				delete_temp_process(t_list **head);
void				add_temp_process(t_arena *arena);
void				ft_list_remove_nb_cycle_0(t_arena *arena);

/*
** Execute instructions
*/
t_op				g_op_tab[17];
void				exec_live(t_env *env, t_arena *arena, t_process *process);
void				exec_ld(t_arena *arena, t_process *process);
void				exec_st(t_arena *arena, t_process *process);
void				exec_add(t_arena *arena, t_process *process);
void				exec_sub(t_arena *arena, t_process *process);
void				exec_and(t_arena *arena, t_process *process);
void				exec_or(t_arena *arena, t_process *process);
void				exec_xor(t_arena *arena, t_process *process);
void				exec_zjmp(t_arena *arena, t_process *process);
void				exec_ldi(t_arena *arena, t_process *process);
void				exec_sti(t_arena *arena, t_process *process);
void				exec_fork(t_arena *arena, t_process *process);
void				exec_lld(t_arena *arena, t_process *process);
void				exec_lldi(t_arena *arena, t_process *process);
void				exec_lfork(t_arena *arena, t_process *process);
void				exec_aff(t_arena *arena, t_process *process);

/*
** Get params
*/
int					params_length(t_params params, int opcode);
int					valid_params(t_params params, int opcode);
unsigned int		get_long_ind_value(t_arena *arena,
					t_process *process, int *add_to_pc);
unsigned int		get_ind_value(t_arena *arena,
					t_process *process, int *add_to_pc);
unsigned int		get_dir_value(t_arena *arena,
					t_process *process, int *add_to_pc);
int					ft_check(t_arena *arena, t_process *process,
						t_params *params, int *add_to_pc);
int					ft_check_register(t_arena *arena, t_process *process,
						int add_to_pc, t_params params);

/*
** Visualizer
*/
void				display_arena_ncurses(t_env *env, t_arena *arena);
int					display_ncurses(t_cell *cell, t_env *env);
void				ft_exit();
void				ft_winner(t_env *env);
void				ft_text(WINDOW *stdscr, t_env *env);
void				ft_champion(t_list **head);

#endif
