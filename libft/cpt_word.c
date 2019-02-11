/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpt_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:18:40 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/17 13:19:33 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		cpt_word(char *str)
{
	int i;
	int nbword;
	int vide;

	vide = 1;
	i = 0;
	nbword = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
		{
			i++;
			vide = 1;
		}
		else
		{
			if (vide == 1)
				nbword++;
			vide = 0;
			i++;
		}
	}
	return (nbword);
}
