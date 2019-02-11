/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 09:38:25 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/30 14:21:12 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int	ft_binary_to_hexa(int binary)
{
	int decimal_val;
	int base;
	int rem;

	decimal_val = 0;
	base = 1;
	while (binary > 0)
	{
		rem = binary % 10;
		decimal_val = decimal_val + rem * base;
		binary = binary / 10;
		base = base * 2;
	}
	return (decimal_val);
}

int	ft_ended(char car)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (car == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_verify_label(char *line)
{
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(line);
	while (trimmed[i] != LABEL_CHAR)
	{
		if (ft_ended(trimmed[i]) == 1)
			i++;
		else
		{
			ft_strdel(&trimmed);
			return (0);
		}
	}
	i++;
	if (trimmed[i] != 0 && trimmed[i] != 32 && trimmed[i] != 9
				&& trimmed[i] != COMMENT_CHAR)
	{
		ft_strdel(&trimmed);
		return (0);
	}
	ft_strdel(&trimmed);
	return (1);
}

int	ft_without_label(char **line)
{
	int		i;
	char	*trimmed;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(*line);
	while (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '\0')
		i++;
	trimmed = ft_strsub(tmp, 0, i);
	ft_strdel(&tmp);
	trimmed = no_space_after_inst(trimmed, line);
	i = 0;
	while (i != 16)
	{
		if (!ft_strcmp(trimmed, g_op_tab[i].instruction_name))
		{
			ft_strdel(&trimmed);
			return (1);
		}
		i++;
	}
	ft_strdel(&trimmed);
	return (0);
}
