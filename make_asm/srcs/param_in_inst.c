/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_in_inst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_param		*write_param(int type, int value, char *label, int size)
{
	t_param *param;

	if (!(param = (t_param*)malloc(sizeof(t_param))))
		return (NULL);
	param->value = value;
	param->type = type;
	param->label = ft_strdup(label);
	param->size = size;
	return (param);
}

int			param_is_reg(t_instruction *inst, t_param *param, char *param_l)
{
	if (ft_strlen(param_l) > 4)
		return (4);
	if (atoi(&param_l[1]) < 1
			|| atoi(&param_l[1]) > REG_NUMBER)
		return (4);
	param = write_param(T_REG, atoi(&param_l[1]), NULL, 1);
	ft_list_push_back(&(inst->head_params), param, sizeof(t_param));
	free(param);
	param = NULL;
	return (1);
}

int			param_is_dir(t_instruction *inst, t_param *param, char *param_l)
{
	int size;

	if (g_op_tab[return_info_inst(inst->instruction)].the_bool)
		size = 2;
	else
		size = 4;
	if (param_l[1] == LABEL_CHAR)
		param = write_param(T_DIR, 0, &param_l[2], size);
	else if (ft_str_isdigit(&param_l[1]))
		param = write_param(T_DIR, atoi(&param_l[1]), NULL, size);
	else
		return (4);
	ft_list_push_back(&(inst->head_params), param, sizeof(t_param));
	free(param);
	param = NULL;
	return (1);
}

int			param_is_ind(t_instruction *inst, t_param *param, char *param_l)
{
	if (param_l[0] == LABEL_CHAR)
		param = write_param(T_IND, 0, &param_l[1], 2);
	else if (ft_str_isdigit(&param_l[1]))
		param = write_param(T_IND, atoi(&param_l[0]), NULL, 2);
	else
		return (4);
	ft_list_push_back(&(inst->head_params), param, sizeof(t_param));
	free(param);
	param = NULL;
	return (1);
}

int			keep_param(char **param_l, t_instruction *inst)
{
	t_param			*param;
	unsigned int	i;
	int				ok;

	ok = 1;
	i = -1;
	while (param_l[++i])
	{
		param = NULL;
		if (param_l[i][0] == 'r')
			ok = param_is_reg(inst, param, param_l[i]);
		else if (param_l[i][0] == DIRECT_CHAR)
			ok = param_is_dir(inst, param, param_l[i]);
		else
			ok = param_is_ind(inst, param, param_l[i]);
		if (ok != 1)
			break ;
	}
	if (ok != 1)
		return (ok);
	if (g_op_tab[return_info_inst(inst->instruction)].number_of_params != i)
		return (5);
	return (ok);
}
