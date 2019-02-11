/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:43:56 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/17 15:24:52 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "../../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct		s_label
{
	char			*label;
}					t_label;

typedef struct		s_param
{
	int				type;
	int				value;
	char			*label;
	int				size;
}					t_param;

typedef struct		s_instruction
{
	t_list			*head_label;
	char			*instruction;
	int				kind_of_params;
	t_list			*head_params;
	int				size;
}					t_instruction;

typedef struct		s_all_info
{
	char			*name;
	char			*commentaire;
	int				size;
	t_list			*head_inst;
	int				fd;
	int				ret;
	int				nb_line;
	int				error;
}					t_all_info;

typedef struct		s_opc
{
	unsigned char	nb1 : 8;
	unsigned char	nb2 : 8;
	unsigned char	nb3 : 8;
	unsigned char	nb4 : 8;
}					t_opc;

typedef struct		s_error
{
	char*			type_error;
}					t_error;

t_error				g_error_tab[14];
int					free_and_return(char *name, char *other_line,
					int to_return);
int					return_info_inst(char *inst);
t_all_info			*ft_init(int fd);
int					check_if_babel_exist(t_instruction *inst, t_all_info *all);
int					label_exist(t_all_info *all);
int					find_label(t_all_info *all, t_param *param);
int					ft_verify_label(char *line);
int					ft_without_label(char **line);
void				write_cor_file(t_all_info *all, char *arg);
void				print_to_fd(int value, int size, int fd);
int					find_index_label(t_all_info *all,
					t_param *param, int index);
void				print_header_type(char *type, int size, int fd);
int					ft_binary_to_hexa(int binary);
int					keep_param(char **param_l, t_instruction *inst);
int					find_ocp(t_instruction *inst, t_op op, int *size, int i);
char				*part_of_ocp(t_param *param, int *size, t_op op);
t_instruction		*keep_instruction(char *line, int id,
					t_all_info *all, t_instruction *inst);
int					keep_name(char *line, int id, t_all_info *all);
int					ft_all(char **line, t_all_info *all, int *in_header);
int					ft_strniels(const char *s, int c);
char				*ft_strtronc(char *str, int n);
char				**free_double_tab(char **tab);
void				del_params(t_instruction *inst);
void				*error(int error, int line);
char				**in_next_line(char *line, int index);
int					write_inst(char **info, t_instruction *inst, int *size);
int					empty(char *str);
void				del_all_info(t_all_info *all);
int					ft_str_isdigit(char *str);
char				*no_space(char *s);
char				*label_without_comm(char *str);
char				*line_no_comment(char *line,
					t_all_info *all, t_instruction *inst);
int					ft_lstcmp(t_instruction *inst, char *str);
void				put_label_in_inst(t_instruction *inst, char *str);
int					all_param(char **info, int index);
t_label				*write_label(char *str);
char				*line_without_comm(char *str);
int					check_comm(char *str);
char				*no_space_after_inst(char *str, char **line);
int					check_syntax_param(char **tab, char *str);
int					ft_ended(char car);
int					check_syntax(t_all_info *all, char *line);
t_instruction		*ft_init_inst(void);

#endif
