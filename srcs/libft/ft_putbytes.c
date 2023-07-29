/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:34:11 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:31:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbits(unsigned char byte)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 8;
	while (i < size)
	{
		if ((byte & (0b10000000 >> i)))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i++;
	}
}

/*
** size in bytes. use with sizeof()
*/
void	ft_putbytes(void *bytes, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = bytes;
	while (i < size)
	{
		ft_putbits(s[i]);
		i++;
		write(1, " ", 1);
		if (i && !(i % 32))
			write(1, "\n", 1);
		else if (!(i % 4))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
