/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:21:48 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 10:59:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** if the host is little endian (which means different from network byte order)
** convert the big endian network bytes to little endian, according to the data
** size passed (which should be, sizeof (t_u32bits, t_u16bit, and so on...)).
** Valid data sizes are 8*, 16 and 32.
** In the case of 8 bytes, bitfields are inverted on the size of 4.
** Usage: hostbyteorder(&int, sizeof(int));
*/

void invert_byteorder(void *value, size_t datasize)
{
	if (datasize == sizeof(t_u32bits))
		*(t_u32bits*)(value) = invert_bytes32(*(t_u32bits*)(value));
	else if (datasize == sizeof(t_u16bits))
		*(t_u16bits*)(value) = invert_bytes16(*(t_u16bits*)(value));
	else if (datasize == sizeof(t_u8bits))
		*(t_u8bits*)(value) = invert_bitfield8(*(t_u8bits*)(value));
}

/*
** These two functions will only invert if host is little endian.
** both functions are actually the same, since conversion will only happen if
** host is little endian.
** The original implementation actually aliases both functions, which is
** something I did not know was possible. Below, the original implementation:
**
**  uint16_t htons (uint16_t x)
**  {
**  #if BYTE_ORDER == BIG_ENDIAN
**    return x;
**  #elif BYTE_ORDER == LITTLE_ENDIAN
**    return __bswap_16 (x);
**  #else
**  # error "What kind of system is this?"
**  #endif
**  }
**  weak_alias (htons, ntohs)
*/
void hostbyteorder(void *value, size_t datasize)
{
	if (!(host_is_littleendian()))
		return ;
	invert_byteorder(value, datasize);
}

void networkbyteorder(void *value, size_t datasize)
{
	hostbyteorder(value, datasize);
}
