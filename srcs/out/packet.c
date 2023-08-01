/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:00:49 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** Sets the data values right after the icmp header.
** Consists of 8 bytes of datetime, and the  rest of the 
*/
static void	fill_pattern(t_ping *ft_ping, char *data)
{
	size_t	i;
	size_t	custom_size;
	size_t	fill_size;

	i = 0;
	fill_size = ft_ping->opts.size;
	if (fill_size >= sizeof(t_time))
	{
		data += sizeof(t_time);
		fill_size -= sizeof(t_time);
	}
	custom_size = ft_ping->opts.pattern.size;
	while (i < fill_size)
	{
		if (custom_size)
			data[i] = ft_ping->opts.pattern.pattern[i % custom_size];
		else
			data[i] = i % (0xff + 1);
		i++;
	}
}

/*
** builds the packet with the pattern that will be used by all ping_outs...
** only sequence, timestamp and checksum are left to be filled.
** function is called by ping only once, before start looping.
*/
void	prebuild_packet(t_ping *ft_ping)
{
	t_headers	hdrs;

	ft_bzero(ft_ping->out.packet, sizeof(ft_ping->out.packet));
	hdrs.icmp = (t_icmp *)(ft_ping->out.packet);
	hdrs.data = (char *)(ft_ping->out.packet) + sizeof(t_icmp);
	hdrs.icmp->un.echo.id = htons(ft_ping->pid);
	hdrs.icmp->type = ICMP_ECHO;
	hdrs.icmp->code = 0;
	fill_pattern(ft_ping, hdrs.data);
}

/*
** Packet consists of icmp header + data
** ICMP header + default size = 64.
** function is called by ping_out before each loop.
*/
void	build_packet(t_ping *ft_ping)
{
	t_time		now;
	t_headers	hdrs;

	hdrs.datalen = ft_ping->opts.size;
	hdrs.icmp = (t_icmp *)(ft_ping->out.packet);
	hdrs.data = (char *)(ft_ping->out.packet) + sizeof(t_icmp);
	hdrs.icmp->un.echo.sequence = htons(ft_ping->out.count);
	clear_duptrack(ft_ping, ft_ping->out.count);
	if (ft_ping->opts.size >= sizeof(t_time))
	{
		gettimeofday(&now, NULL);
		ft_memcpy(hdrs.data, &now, sizeof(t_time));
	}
	hdrs.icmp->checksum = 0;
	hdrs.icmp->checksum = checksum(hdrs.icmp, hdrs.datalen
			+ sizeof(t_icmp));
}
