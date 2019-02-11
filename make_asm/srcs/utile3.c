/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2019/01/30 14:21:52 by alanter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*line_without_comm(char *str)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			break ;
		i++;
	}
	tmp = ft_strndup(str, i);
	ft_strdel(&str);
	return (tmp);
}

char			*no_space_after_inst(char *str, char **line)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (str[i])
	{
		if (str[i] == DIRECT_CHAR)
		{
			tmp = ft_strndup(str, i);
			ft_strdel(line);
			tmp2 = ft_strjoin(tmp, " ");
			*line = ft_strjoin(tmp2, &str[i]);
			ft_strdel(&tmp2);
			ft_strdel(&str);
			return (tmp);
		}
		i++;
	}
	return (str);
}

int				nbr_char(char *str)
{
	int		i;
	int		nbr_print;

	nbr_print = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != '\t')
			nbr_print++;
		i++;
	}
	return (nbr_print);
}

char			*no_space(char *s)
{
	char	*str;
	int		nbr_print;
	int		i;

	i = 0;
	if (!s)
		return (0);
	nbr_print = nbr_char(s);
	if (!(str = ft_strnew(nbr_print + 1)))
		return (0);
	nbr_print = 0;
	while (s[i])
	{
		if (s[i] != 32 && s[i] != '\t')
		{
			str[nbr_print] = s[i];
			nbr_print++;
		}
		i++;
	}
	str[nbr_print] = '\0';
	return (str);
}

t_instruction	*ft_init_inst(void)
{
	t_instruction	*inst;

	if (!(inst = (t_instruction*)malloc(sizeof(t_instruction))))
		return (0);
	inst->head_label = NULL;
	inst->instruction = NULL;
	inst->kind_of_params = 0;
	inst->size = 0;
	inst->head_params = NULL;
	return (inst);
}
