/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_in_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*part_of_ocp(t_param *param, int *size, t_op op)
{
	if (param->type == 1)
	{
		*size = *size + 1;
		return ("01");
	}
	else if (param->type == 2)
	{
		if (op.the_bool)
			*size = *size + 2;
		else
			*size = *size + 4;
		return ("10");
	}
	else
	{
		*size = *size + 2;
		return ("11");
	}
}

int			find_ocp(t_instruction *inst, t_op op, int *size, int i)
{
	char			*ocp_char;
	int				ocp;
	t_param			*param;
	t_list			*head_temp_param;

	*size = 1 + op.with_oct;
	ocp_char = malloc(sizeof(char) * 9);
	ft_bzero(ocp_char, 9);
	head_temp_param = inst->head_params;
	while (head_temp_param)
	{
		param = (t_param*)(head_temp_param->content);
		if (!(param->type & op.kind_params[i++]))
		{
			ft_strdel(&ocp_char);
			return (0);
		}
		ocp_char = ft_strcat(ocp_char, part_of_ocp(param, size, op));
		head_temp_param = head_temp_param->next;
	}
	while (strlen(ocp_char) < 8)
		ocp_char = ft_strcat(ocp_char, "00");
	ocp = ft_binary_to_hexa(ft_atoi(ocp_char));
	ft_strdel(&ocp_char);
	return (ocp);
}

int			init_ocp(t_instruction *inst, int *size, int op_index)
{
	int		ocp;

	ocp = find_ocp(inst, g_op_tab[op_index], size, 0);
	if (!ocp)
		return (6);
	if (g_op_tab[op_index].with_oct)
		inst->kind_of_params = ocp;
	else
		inst->kind_of_params = 0;
	return (1);
}

int			write_inst(char **info, t_instruction *inst, int *size)
{
	int		op_index;
	char	**param;
	char	*ins;
	int		ok;

	op_index = return_info_inst(info[1]);
	if (op_index == 16)
	{
		return (3);
	}
	ins = ft_strdup(info[1]);
	inst->instruction = ins;
	param = ft_strsplit(info[2], SEPARATOR_CHAR);
	if ((ok = check_syntax_param(param, info[2])) == 1)
		ok = keep_param(param, inst);
	free_double_tab(param);
	if (ok != 1)
		return (ok);
	ok = init_ocp(inst, size, op_index);
	return (ok);
}

int			all_param(char **info, int index)
{
	int		comm;
	int		i;

	i = 1;
	while (info[i + index + 1])
	{
		comm = ft_strniels(info[i + index + 1], COMMENT_CHAR);
		if (comm != -1)
		{
			if (comm == 0)
				return (i);
			info[i + index + 1] = ft_strtronc(info[i + index + 1], comm);
			info[1 + index] = ft_strcat(info[1 + index], info[i + index + 1]);
			i++;
			return (i);
		}
		info[1 + index] = ft_strcat(info[1 + index], info[i + index + 1]);
		i++;
	}
	return (i);
}
