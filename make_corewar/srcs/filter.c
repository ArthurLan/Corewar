/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:17:00 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 12:17:00 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	delete_temp_process(t_list **head)
{
	t_list	*current_process;
	t_list	*tmp;

	if (head != NULL)
	{
		current_process = *head;
		while (current_process)
		{
			tmp = current_process->next;
			free(current_process->content);
			current_process->content = 0;
			free(current_process);
			current_process = tmp;
		}
	}
}

void	delete_node(t_arena *arena, t_list *list_ptr,
	t_list *list_parent, t_list *tmp)
{
	t_process	*process;

	process = ((t_process*)(list_ptr->content));
	arena->cell[(process->pos + process->pc) % MEM_SIZE].color = 37;
	if (list_parent != 0)
		list_parent->next = list_ptr->next;
	else
		arena->process = tmp;
	arena->nb_process--;
	free(list_ptr->content);
	list_ptr->content = 0;
	free(list_ptr);
	list_ptr = 0;
}

void	ft_list_remove_nb_cycle_0(t_arena *arena)
{
	t_list		**head;
	t_list		*list_ptr;
	t_list		*list_parent;
	t_list		*tmp;
	t_process	*process;

	head = &(arena->process);
	list_ptr = *head;
	list_parent = 0;
	while (list_ptr)
	{
		tmp = list_ptr->next;
		process = ((t_process*)(list_ptr->content));
		if (process->nb_live == 0)
			delete_node(arena, list_ptr, list_parent, tmp);
		else
		{
			process->nb_live = 0;
			list_parent = list_ptr;
		}
		list_ptr = tmp;
	}
}

void	add_temp_process(t_arena *arena)
{
	t_list	*process_list;

	process_list = arena->temp_process;
	while (process_list)
	{
		ft_list_push_front(&(arena->process),
		(t_process*)process_list->content, sizeof(t_process));
		process_list = process_list->next;
	}
	delete_temp_process(&(arena->temp_process));
	arena->temp_process = NULL;
}
