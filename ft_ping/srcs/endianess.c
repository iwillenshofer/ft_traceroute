/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:04:06 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:54:38 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool host_is_littleendian(void)
{
	short i;

	i = 1;
	if (*(char*)(&i))
		return (true);
	return (false);
}

/*
** The following three functions are simple bitwise functions to invert the
** bytes of 64(8), 32(4), and 16(2) bits(bytes) datatypes.
*/

t_u16bits bytes16_le(t_u16bits hostshort)
{
	t_u16bits newshort;

	if (!(host_is_littleendian()))
		return (hostshort);
	newshort = 0;
	newshort = newshort | ((hostshort & 0xff00) >> 8);
	newshort = newshort | ((hostshort & 0x00ff) << 8);
	return (newshort);
}

t_u32bits bytes32_le(t_u32bits hostlong)
{
	t_u32bits newlong;

	if (!(host_is_littleendian()))
		return (hostlong);
	newlong = 0;
	newlong = newlong | ((hostlong & 0xff000000) >> 24);
	newlong = newlong | ((hostlong & 0x00ff0000) >> 8);
	newlong = newlong | ((hostlong & 0x0000ff00) << 8);
	newlong = newlong | ((hostlong & 0x000000ff) << 24);
	return (newlong);
}

/*
** Just like the inversion of bytes, a bitfield may also need
** to be switched (as in the case of ) s_ipheader->ihl/version;
*/
t_u8bits bitfield8_le(t_u8bits hostshort)
{
	t_u8bits newshort;
	if (!(host_is_littleendian()))
		return (hostshort);
	newshort = 0;
	newshort = newshort | ((hostshort & 0xf0) >> 4);
	newshort = newshort | ((hostshort & 0x0f) << 4);
	return (newshort);
}
