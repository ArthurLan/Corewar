/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   melting_pot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:42:41 by ncohen            #+#    #+#             */
/*   Updated: 2018/12/03 14:42:45 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		put_label_in_inst(t_instruction *inst, char *str)
{
	t_label	*label;

	if (!(label = (t_label*)malloc(sizeof(t_label))))
		return ;
	label->label = ft_strdup(label_without_comm(str));
	ft_list_push_back(&(inst->head_label), label, sizeof(t_label));
	free(label);
}

char		*save_label_last_line(char *str, t_instruction *inst)
{
	char	**split;
	char	*tmp;

	tmp = ft_strdup(str);
	tmp = no_space_after_inst(tmp, &str);
	ft_strdel(&tmp);
	split = ft_split_whitespaces(str);
	if (split[1] && split[0][ft_strlen(split[0]) - 1] == LABEL_CHAR)
	{
		split[0][ft_strlen(split[0]) - 1] = '\0';
		put_label_in_inst(inst, split[0]);
		free_double_tab(split);
		tmp = ft_strdup(&ft_strchr(str, LABEL_CHAR)[1]);
		ft_strdel(&str);
		return (tmp);
	}
	free_double_tab(split);
	return (str);
}

int			add_other_label(char *line, t_all_info *all
				, t_instruction *inst, char *t)
{
	t = no_space(line);
	if ((t[0] != COMMENT_CHAR && !ft_verify_label(t)) || all->ret < 1)
	{
		ft_strdel(&t);
		return (0);
	}
	if (ft_verify_label(line))
		put_label_in_inst(inst, t);
	ft_strdel(&t);
	return (1);
}

char		*line_no_comment(char *line, t_all_info *all, t_instruction *inst)
{
	put_label_in_inst(inst, line);
	ft_strdel(&line);
	while ((all->ret = get_next_line(all->fd, &line)) > 0)
	{
		all->nb_line += 1;
		line = line_without_comm(line);
		if (!check_syntax(all, line))
		{
			ft_list_push_back(&(all->head_inst), inst, sizeof(t_instruction));
			ft_strdel(&line);
			return (NULL);
		}
		if (ft_strlen(line) > 0 && !empty(line))
			if (!add_other_label(line, all, inst, NULL))
				break ;
		ft_strdel(&line);
	}
	if (all->ret < 1)
	{
		ft_list_push_back(&(all->head_inst), inst, sizeof(t_instruction));
		return (NULL);
	}
	return (save_label_last_line(line, inst));
}
