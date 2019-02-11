/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	**free_double_tab(char **tab)
{
	int		i;

	if (tab)
	{
		if (tab[0])
			ft_strdel(&tab[0]);
		if (tab[1])
		{
			i = 1;
			while (tab[i])
			{
				ft_strdel(&tab[i]);
				i++;
			}
		}
		free(tab);
		tab = NULL;
	}
	return (NULL);
}

void	del_params(t_instruction *inst)
{
	t_list	*tmp_param;
	t_param *param;

	while (inst->head_params)
	{
		tmp_param = inst->head_params->next;
		param = (t_param*)inst->head_params->content;
		ft_strdel(&(param->label));
		free(param);
		param = NULL;
		free(inst->head_params);
		inst->head_params = tmp_param;
	}
}

void	del_label(t_instruction *inst)
{
	t_list	*tmp_label;
	t_label *label;

	while (inst->head_label)
	{
		tmp_label = inst->head_label->next;
		label = (t_label*)inst->head_label->content;
		ft_strdel(&(label->label));
		free(label);
		label = NULL;
		free(inst->head_label);
		inst->head_label = tmp_label;
	}
}

void	del_all_info(t_all_info *all)
{
	t_list			*tmp;
	t_instruction	*inst;

	ft_strdel(&(all->name));
	ft_strdel(&(all->commentaire));
	all->fd = close(all->fd);
	while (all->head_inst)
	{
		tmp = all->head_inst->next;
		inst = (t_instruction*)all->head_inst->content;
		del_params(inst);
		del_label(inst);
		ft_strdel(&(inst->instruction));
		free(inst);
		inst = NULL;
		free(all->head_inst);
		all->head_inst = tmp;
	}
	free(all);
	all = NULL;
}
