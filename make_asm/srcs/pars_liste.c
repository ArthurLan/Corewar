/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_liste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/30 14:20:58 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_index_label(t_all_info *all, t_param *param, int index)
{
	t_list			*head_temp;
	t_instruction	*inst;
	int				dif_index;

	dif_index = -index;
	head_temp = all->head_inst;
	inst = (t_instruction*)(head_temp->content);
	if ((inst->head_label && ft_lstcmp(inst, param->label)))
	{
		return (dif_index);
	}
	while (head_temp && ((inst->head_label && !ft_lstcmp(inst, param->label))
			|| !inst->head_label))
	{
		inst = (t_instruction*)(head_temp->content);
		dif_index = dif_index + (inst->size);
		head_temp = head_temp->next;
	}
	return (dif_index - inst->size);
}

void	pars_params(t_instruction *inst, t_all_info *all, int all_size, int fd)
{
	t_param			*param;
	t_list			*head_temp_param;
	int				index_of_label;

	head_temp_param = inst->head_params;
	while (head_temp_param)
	{
		param = (t_param*)(head_temp_param->content);
		if (!param->label)
			print_to_fd(param->value, param->size, fd);
		else
		{
			index_of_label = find_index_label(all, param, all_size);
			print_to_fd(index_of_label, param->size, fd);
		}
		head_temp_param = head_temp_param->next;
	}
}

void	pars_insts(t_all_info *all, int fd)
{
	t_instruction	*inst;
	t_list			*head_temp;
	unsigned char	c;

	all->size = 0;
	head_temp = all->head_inst;
	while (head_temp)
	{
		inst = (t_instruction*)(head_temp->content);
		c = (unsigned char)(return_info_inst(inst->instruction) + 1);
		if (inst->head_params)
			write(fd, &c, 1);
		if (inst->kind_of_params)
		{
			c = (unsigned char)(inst->kind_of_params);
			write(fd, &c, 1);
		}
		pars_params(inst, all, all->size, fd);
		all->size = all->size + inst->size;
		head_temp = head_temp->next;
	}
}

void	pars_header(t_all_info *all, int fd)
{
	print_to_fd(COREWAR_EXEC_MAGIC, 4, fd);
	print_header_type(all->name, PROG_NAME_LENGTH, fd);
	print_to_fd(all->size, 4, fd);
	print_header_type(all->commentaire, COMMENT_LENGTH, fd);
}

void	write_cor_file(t_all_info *all, char *arg)
{
	int		fd;
	char	*title;
	char	*tmp;

	title = ft_strndup(arg, ft_strlen(arg) - 2);
	tmp = ft_strjoin(title, ".cor");
	ft_putstr_fd("Writing output program to ", 1);
	ft_putstr_fd(tmp, 1);
	ft_putchar_fd('\n', 1);
	fd = open(tmp, O_CREAT | O_TRUNC | O_RDWR, 0666);
	ft_strdel(&tmp);
	pars_header(all, fd);
	pars_insts(all, fd);
	close(fd);
	ft_strdel(&title);
}
