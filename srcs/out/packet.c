/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:00:49 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/02 21:06:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** In udp socket, we just need to set up data
** Although packet size may vary, we will build the whole packet up to the 
** max packet size (65000) with a loop starting at 0x00 and ending at 0x7f
*/
void	build_packet(t_trace *tr)
{
	size_t	i;

	i = 0;
	while (i < sizeof(tr->out.packet))
	{
		tr->out.packet[i] = i % ((0x7f - 0x40) + 1) + 0x40;
		i++;
	}
}
