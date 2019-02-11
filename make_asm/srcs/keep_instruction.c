/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			**inst_in_one_block(char **info, char *line)
{
	char	*inst;
	char	*param;

	inst = ft_strdup(info[0]);
	param = ft_strdup(info[1]);
	free_double_tab(info);
	info = (char**)malloc(sizeof(char*) * (cpt_letter(line) + 20));
	info[0] = NULL;
	info[1] = inst;
	info[2] = param;
	info[3] = NULL;
	return (info);
}

char			**no_inst_in_line(char **info, t_all_info *all
			, char *line, t_instruction *inst)
{
	char	**in_next;

	line = line_no_comment(ft_strdup(info[0]), all, inst);
	free_double_tab(info);
	if (!line)
		return (NULL);
	if (!(char*)((t_label*)(inst->head_label->content))->label)
	{
		all->error = 7;
		return (NULL);
	}
	in_next = in_next_line(line, 0);
	ft_strdel(&line);
	if (!in_next)
		return (NULL);
	if (!(info = (char**)malloc(sizeof(char*) * (ft_strlen(line) + 4))))
		return (NULL);
	info[0] = NULL;
	info[1] = ft_strdup(in_next[0]);
	info[2] = ft_strdup(in_next[1]);
	info[3] = NULL;
	free_double_tab(in_next);
	return (info);
}

char			**is_label(char **info, t_all_info *all
			, char *line, t_instruction *inst)
{
	char	**in_next;

	if (!info[1] || info[1][0] == COMMENT_CHAR)
		return (no_inst_in_line(info, all, line, inst));
	else if (info[2] && info[2][ft_strlen(info[2]) - 1] == SEPARATOR_CHAR)
	{
		in_next = in_next_line(line, 1);
		if (!in_next)
			return (free_double_tab(info));
		ft_strdel(&info[2]);
		info[2] = ft_strdup(in_next[2]);
		ft_strdel(&info[1]);
		info[1] = ft_strdup(in_next[1]);
		free_double_tab(in_next);
	}
	else if (!info[2] || (info[3] && info[3][0] != COMMENT_CHAR))
		return (free_double_tab(info));
	if (info)
		put_label_in_inst(inst, info[0]);
	return (info);
}

char			**is_not_label(char **info, char *line)
{
	char	**in_next;

	if ((info[1] && info[1][ft_strlen(info[1]) - 1] == SEPARATOR_CHAR)
			|| (info[2] && info[2][0] == SEPARATOR_CHAR))
	{
		in_next = in_next_line(line, 0);
		free_double_tab(info);
		if (!in_next)
			return (NULL);
		info = (char**)malloc(sizeof(char*) * (cpt_letter(line) + 20));
		info[2] = ft_strdup(in_next[1]);
		info[1] = ft_strdup(in_next[0]);
		info[3] = NULL;
		free_double_tab(in_next);
	}
	else if (info[1] && (!info[2] || info[2][0] == COMMENT_CHAR))
		info = inst_in_one_block(info, line);
	else
		return (free_double_tab(info));
	info[0] = NULL;
	return (info);
}

t_instruction	*keep_instruction(char *line, int id, t_all_info *all,
					t_instruction *inst)
{
	char	**info;
	int		size_of_inst;

	size_of_inst = 0;
	info = ft_split_whitespaces(line);
	info = id == 1 ? is_label(info, all, line, inst)
		: is_not_label(info, line);
	if (!info && all->error != 1)
	{
		all->error = 7;
		return (NULL);
	}
	if (!info && (all->error = 1))
		return (NULL);
	all->error = write_inst(info, inst, &size_of_inst);
	free_double_tab(info);
	if (all->error != 1)
	{
		ft_list_push_back(&(all->head_inst), inst, sizeof(t_instruction));
		return (NULL);
	}
	inst->size = size_of_inst;
	all->size = all->size + inst->size;
	return (inst);
}
