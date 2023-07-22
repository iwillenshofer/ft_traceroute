/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_byte.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:30:03 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 09:49:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_print_hex_byte(unsigned char c)
{
	if (c < 10)
		c += '0';
	else
		c += 'a' - 10;
	ft_putchar(c);
}

void	ft_puthexbyte(unsigned char c)
{
	unsigned char	n1;
	unsigned char	n2;

	n1 = c / 16;
	n2 = c % 16;
	_print_hex_byte(n1);
	_print_hex_byte(n2);
}

/*
** size in bytes. use with sizeof()
*/
void	ft_puthex_bytes(void *bytes, size_t size)
{
	char *s;
	size_t i;

	i = 0;
	s = bytes;
	while (i < size)
	{
		ft_puthexbyte(s[i]);
		write(1, " ", 1);
		i++;
		if (!(i % 32))
			write(1, "\n", 1);
		else if (!(i % 4))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
