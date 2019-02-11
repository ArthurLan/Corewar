/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:48:37 by clecalie          #+#    #+#             */
/*   Updated: 2018/03/12 16:07:54 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		result;

	if (!str)
		return (0);
	neg = 0;
	i = 0;
	result = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str && str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - '0';
	if (neg)
		result = -result;
	return (result);
}
