/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:25:33 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/12 14:26:54 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** calculates the checksum.
** best source ever: https://www.ietf.org/rfc/rfc1071.txt
*/

t_u16bits	calculate_checksum(void *buffer, size_t size)
{
	size_t		i;
	t_u8bits	*data;
	t_u32bits	sum;
	t_u16bits	last_elem;

	i = 0;
	sum = 0;
	last_elem = 0;
	data = buffer;
	if (size % 2)
	{
		size--;
		last_elem = (data[size]) << 8;
	}
	while (i < size)
	{
		sum += *(t_u16bits *)(&data[i]);
		i += 2;
	}
	if (last_elem)
		sum += (last_elem << 8);
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (~sum);
}