/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncohen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:41:49 by ncohen            #+#    #+#             */
/*   Updated: 2018/11/20 14:50:50 by ncohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	suit_print(int value, int fd)
{
	unsigned char	t1;
	unsigned char	t2;
	unsigned char	t3;
	unsigned char	t4;
	t_opc			test;

	test = *(t_opc*)&value;
	t1 = test.nb1;
	t2 = test.nb2;
	t3 = test.nb3;
	t4 = test.nb4;
	write(fd, &t4, 1);
	write(fd, &t3, 1);
	write(fd, &t2, 1);
	write(fd, &t1, 1);
}

void	print_to_fd(int value, int size, int fd)
{
	int				i;
	unsigned char	t1;
	unsigned char	t2;
	t_opc			test;

	if (size == 1)
	{
		i = (unsigned char)(value);
		write(fd, &i, 1);
	}
	else if (size == 2)
	{
		i = (unsigned short)(value);
		test = *(t_opc*)&i;
		t1 = test.nb1;
		t2 = test.nb2;
		write(fd, &t2, 1);
		write(fd, &t1, 1);
	}
	else if (size == 4)
		suit_print(value, fd);
}

void	print_header_type(char *type, int size, int fd)
{
	int i;
	int end;

	i = 0;
	end = 0;
	while (i < size + 4)
	{
		if (!end)
		{
			print_to_fd((int)type[i], 1, fd);
			if (!type[i])
				end = 1;
		}
		else
			print_to_fd((int)0, 1, fd);
		i++;
	}
}
