/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:25:10 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/30 14:21:24 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_lstcmp(t_instruction *inst, char *str)
{
	t_list	*head_tmp;
	t_label	*label;

	head_tmp = inst->head_label;
	while (head_tmp)
	{
		label = (t_label*)(head_tmp->content);
		if (!ft_strcmp(label->label, str))
			return (1);
		head_tmp = head_tmp->next;
	}
	return (0);
}

int	check_if_babel_exist(t_instruction *inst, t_all_info *all)
{
	t_param			*param;
	t_list			*head_temp_param;

	head_temp_param = inst->head_params;
	while (head_temp_param)
	{
		param = (t_param*)(head_temp_param->content);
		if (param->label != NULL)
			return (find_label(all, param));
		head_temp_param = head_temp_param->next;
	}
	return (1);
}

int	label_exist(t_all_info *all)
{
	t_instruction	*inst;
	t_list			*head_temp;

	head_temp = all->head_inst;
	if (!head_temp)
		return (11);
	inst = (t_instruction*)(head_temp->content);
	if (!inst)
		return (0);
	while (head_temp)
	{
		inst = (t_instruction*)(head_temp->content);
		if (!check_if_babel_exist(inst, all))
			return (12);
		head_temp = head_temp->next;
	}
	return (1);
}

int	find_label(t_all_info *all, t_param *param)
{
	t_list			*head_temp;
	t_instruction	*inst;

	if (ft_strniels(param->label, COMMENT_CHAR) != -1)
		param->label = ft_strtronc(param->label,
			ft_strniels(param->label, COMMENT_CHAR));
	head_temp = all->head_inst;
	while (head_temp)
	{
		inst = (t_instruction*)(head_temp->content);
		if (inst->head_label && ft_lstcmp(inst, param->label))
			return (1);
		head_temp = head_temp->next;
	}
	return (0);
}
