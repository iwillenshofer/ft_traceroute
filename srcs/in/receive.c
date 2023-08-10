/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:58:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 07:43:07 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static t_probe	*getprobe(t_trace *tr, in_port_t port)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < tr->opts.maxhop)
	{
		j = 0;
		while (j < tr->opts.maxhop)
		{
			if (tr->hop[i].probe[j].port == port)
				return (&(tr->hop[i].probe[j]));
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
** checks for the icmp packet stored in tr->in.buf
** drops the packet (returns valid = 0) if not a valid header (ip+icmp)
*/
static t_headers	check_icmp(t_trace *tr, size_t size)
{
	t_headers	header;

	ft_bzero(&header, sizeof(t_headers));
	if (size < (sizeof(t_ip) * 2) + sizeof(t_udp) + sizeof(t_icmp))
		return (header);
	ft_memcpy(&(header.ip), tr->in.buf, sizeof(t_ip));
	if (ntohs(header.ip.tot_len) > size
		|| (header.ip.ihl * 4) + sizeof(t_ip)
		+ sizeof(t_udp) + sizeof(t_icmp) > size
		|| header.ip.protocol != IPPROTO_ICMP)
		return (header);
	ft_memcpy(&(header.icmp), tr->in.buf + header.ip.ihl * 4, sizeof(t_icmp));
	ft_memcpy(&(header.oip), tr->in.buf + header.ip.ihl * 4 + sizeof(t_icmp),
		sizeof(t_ip));
	ft_memcpy(&(header.oudp), tr->in.buf + header.ip.ihl * 4 + sizeof(t_icmp)
		+ sizeof(t_ip), sizeof(t_udp));
	header.valid = true;
	return (header);
}

/*
** fills the probe structure with the appropriated received data:
** maily source address and headers (for icmp code checking when printing)
*/
static void	fillprobe(t_probe *probe, t_headers *headers)
{
	gettimeofday(&(probe->tr), NULL);
	probe->elapsed = elapsed_time_ms(probe->ts, probe->tr);
	probe->received = true;
	ft_bzero(&probe->saddr, sizeof(probe->saddr));
	probe->saddr.sin_family = AF_INET;
	probe->saddr.sin_addr = *(struct in_addr *)&(headers->ip.saddr);
	probe->headers = *headers;
}

/*
** receives the packet, drops if invalid, and check if it's the last hop.
*/
void	recvpackets(t_trace *tr)
{
	t_probe				*probe;
	t_headers			headers;
	int					ret;

	ft_bzero(&tr->in.saddr, sizeof(tr->in.saddr));
	tr->in.saddrlen = sizeof(tr->in.saddr);
	ret = recvfrom(tr->in.sock, tr->in.buf,
			sizeof(tr->in.buf), MSG_DONTWAIT,
			(struct sockaddr*)&(tr->in.saddr), &tr->in.saddrlen);
	if (ret > 0)
	{
		headers = check_icmp(tr, (size_t)ret);
		if (!headers.valid)
			return ;
		probe = getprobe(tr, ntohs(headers.oudp.dest));
		if (probe && !(probe->received) && !(probe->timedout))
		{
			fillprobe(probe, &headers);
			if (!ft_memcmp(&probe->daddr.sin_addr, &headers.ip.saddr,
					sizeof(in_addr_t))
				|| headers.icmp.type != ICMP_TIME_EXCEEDED)
				tr->hop[probe->hdx].lasthop = true;
			tr->count.recv++;
		}
	}
}
