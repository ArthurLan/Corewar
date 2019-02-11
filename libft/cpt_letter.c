/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpt_letter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:16:29 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/17 13:19:13 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

int		cpt_letter(char *str)
{
	int i;
	int stop;
	int nbletter;

	nbletter = 0;
	i = 0;
	stop = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
		{
			if (stop == 1)
				return (nbletter);
			i++;
		}
		else
		{
			stop = 1;
			nbletter++;
			i++;
		}
	}
	return (nbletter);
}
