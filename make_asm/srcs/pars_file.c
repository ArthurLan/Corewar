/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/29 14:50:40 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				is_label_inst(t_all_info *all, char *str, char **line)
{
	if (ft_strlen(str) != 0 && ft_without_label(line))
		return (0);
	else if (ft_strlen(str) != 0 && ft_verify_label(*line))
		return (1);
	else if (ft_strlen(str) != 0
			&& str[0] != COMMENT_CHAR)
	{
		all->error = 8;
		return (8);
	}
	else
	{
		all->error = 2;
		return (2);
	}
	return (1);
}

int				ft_check_kind_of_inst(char **line, t_all_info *all)
{
	t_instruction	*inst;
	char			*tmp;
	int				is_label;

	tmp = ft_strtrim(*line);
	is_label = is_label_inst(all, tmp, line);
	ft_strdel(&tmp);
	if (all->error == 2)
		return (1);
	inst = ft_init_inst();
	if (all->error != 1)
	{
		free(inst);
		return (all->error);
	}
	if (all->error == 1 && keep_instruction(*line, is_label, all, inst))
		ft_list_push_back(&(all->head_inst), inst, sizeof(t_instruction));
	else if (all->error == 1)
	{
		del_params(inst);
		ft_strdel(&inst->instruction);
		all->error = 1;
	}
	free(inst);
	return (all->error);
}

int				ft_check_kind_of_header(char *line, t_all_info *all,
					int *in_header)
{
	char	*nospace;

	nospace = no_space(line);
	if (!ft_strncmp(nospace, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
		&& nospace[ft_strlen(NAME_CMD_STRING)] == '"')
		if (!all->name)
			all->error = keep_name(line, 0, all);
		else
			all->error = 0;
	else if (!ft_strncmp(nospace,
			COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))
			&& nospace[ft_strlen(COMMENT_CMD_STRING)] == '"')
	{
		if (!all->commentaire)
			all->error = keep_name(line, 1, all);
		else
			all->error = 0;
	}
	else if (nospace && nospace[0] != COMMENT_CHAR && all->error != 1)
		all->error = 8;
	ft_strdel(&nospace);
	if (all->name && all->commentaire)
		*in_header = 0;
	return (all->error);
}

void			check_error(t_all_info *all, char **line)
{
	*line = line_without_comm(*line);
	check_syntax(all, *line);
	if (all->error == 1)
	{
		if (ft_strlen(all->commentaire) > 2048)
			all->error = 9;
		else if (ft_strlen(all->name) > 128)
			all->error = 10;
		if (all->error == 1)
			all->error = ft_check_kind_of_inst(line, all);
	}
}

int				ft_all(char **line, t_all_info *all, int *in_header)
{
	if (!empty(*line))
	{
		if (!*in_header)
			check_error(all, line);
		else
			all->error = ft_check_kind_of_header(*line, all, in_header);
	}
	if (all->error != 1)
	{
		if (all->error != 17 && !all->commentaire)
			all->error = 13;
		else if (all->error != 17 && !all->name)
			all->error = 14;
		error(all->error, all->nb_line);
	}
	all->nb_line += 1;
	return (all->error);
}
