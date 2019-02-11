/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <clecalie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:22:35 by clecalie          #+#    #+#             */
/*   Updated: 2018/12/04 12:22:42 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	reset_champ_lives(t_list **head)
{
	t_list	*list;
	t_champ	*champ;

	list = *head;
	while (list)
	{
		champ = (t_champ*)list->content;
		champ->nb_live = 0;
		list = list->next;
	}
}

int		champ_alive(t_env *env)
{
	int		i;
	t_list	*champ;

	i = 0;
	champ = env->head_champs;
	while (champ)
	{
		if (((t_champ*)(champ->content))->is_alive)
			i++;
		champ = champ->next;
	}
	return (i);
}

t_champ	*find_champ(t_env *env, unsigned int champ_id)
{
	t_list	*list;
	t_champ	*champ;

	list = env->head_champs;
	while (list)
	{
		champ = (t_champ*)list->content;
		if (champ->id == champ_id)
			return (champ);
		list = list->next;
	}
	return (0);
}
