/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:42:41 by ncohen            #+#    #+#             */
/*   Updated: 2018/12/03 14:42:45 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		empty(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			return (1);
		if (str[i] != 32 && ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_str_isdigit(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_strniels(const char *s, int c)
{
	int		len;
	int		i;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[len])
		len++;
	len++;
	while (i < len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		return_info_inst(char *inst)
{
	int		i;

	i = 0;
	while (i != 16)
	{
		if (!ft_strcmp(inst, g_op_tab[i].instruction_name))
			return (i);
		i++;
	}
	return (16);
}

void	*error(int error, int line)
{
	static t_error error_tab[15] = {
		{"Invalid instruction "}, {"Invalid parameter value "},
		{"Invalid parameter count "}, {"Invalid parameter type "},
		{"Lexical error "}, {"Syntax error "},
		{"Lenght of comment too long"}, {"Lenght of name too long"},
		{"No instruction"}, {"Call label no set"},
		{"No comment set "}, {"No name set"},
		{"Lenght of chamipon too long"}, {"Empty file or not a file"},
		{"Syntax error in header"}
	};

	if (error >= 3 && error < 9)
	{
		ft_putstr_fd(error_tab[error - 3].type_error, 2);
		ft_putstr_fd("at line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (error >= 9 && error < 18)
	{
		ft_putstr_fd(error_tab[error - 3].type_error, 2);
		ft_putchar_fd('\n', 2);
	}
	return (NULL);
}
