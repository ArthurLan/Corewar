/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_syntax(t_all_info *all, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_ended(line[i]) && line[i] != LABEL_CHAR
			&& line[i] != DIRECT_CHAR && line[i] != SEPARATOR_CHAR
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '+'
			&& line[i] != '-' && line[i] != '\0')
		{
			all->error = 7;
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_syntax_param(char **tab, char *str)
{
	int i;
	int nbr;
	int nbr2;

	i = 0;
	nbr = 1;
	nbr2 = 0;
	while (str[i])
	{
		if (str[i] == SEPARATOR_CHAR)
			nbr++;
		i++;
	}
	i = 0;
	while (tab[i])
	{
		nbr2++;
		i++;
	}
	if (nbr == nbr2)
		return (1);
	return (8);
}

int		check_comm(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			return (1);
		if (str[i] != ' ' && str[i] != '\t' && str[i] != COMMENT_CHAR)
			return (17);
		i++;
	}
	return (1);
}
