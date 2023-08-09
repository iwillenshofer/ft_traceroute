/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:25:33 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 01:07:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** calculates the checksum.
** best source ever: https://www.ietf.org/rfc/rfc1071.txt
*/

unsigned short	checksum(void *buffer, size_t size)
{
	size_t			i;
	unsigned char	*data;
	unsigned int	sum;
	unsigned short	last_elem;

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
		sum += *(unsigned short *)(&data[i]);
		i += 2;
	}
	if (last_elem)
		sum += (last_elem << 8);
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (~sum);
}
