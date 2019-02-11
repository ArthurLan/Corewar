/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:19:52 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/22 10:19:55 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (char**)malloc(sizeof(*tab) * (cpt_word(str) + 1));
	while (str[j])
	{
		if (str[j] == '\t' || str[j] == '\n' || str[j] == ' ')
		{
			j++;
		}
		else
		{
			tab[i] = (char*)malloc(sizeof(*tab) * (cpt_letter(&str[j]) + 1));
			ft_strncpy2(tab[i], &str[j], cpt_letter(&str[j]));
			j = j + cpt_letter(&str[j]);
			i++;
		}
	}
	tab[i] = 0;
	return (tab);
}
