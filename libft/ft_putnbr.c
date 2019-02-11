/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:42:51 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/10 15:27:04 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n < -9)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > -9 && n < 0)
	{
		ft_putchar('-');
		ft_putchar(-n + '0');
	}
	else
	{
		ft_putchar(n + '0');
	}
}
