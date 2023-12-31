/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:58:16 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 21:01:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** just to make it clear: A packet is marked as received either
** if we've got it, or if it timed out.
*/
void	sendpackets(t_trace *tr)
{
	t_hop			*hop;
	t_probe			*probe;	

	if ((tr->count.sent > tr->count.recv + tr->count.timedout
			+ tr->opts.squeries && !(tr->count.sent % tr->opts.nqueries))
		|| tr->count.sent >= tr->opts.nqueries * tr->opts.maxhop)
		return ;
	hop = &(tr->hop[tr->count.sent / tr->opts.nqueries]);
	probe = &(hop->probe[tr->count.sent % tr->opts.nqueries]);
	hop->id = tr->count.sent / tr->opts.nqueries;
	hop->ttl = hop->id + tr->opts.firsthop;
	probe->port = tr->opts.port + tr->count.sent;
	probe->sent = true;
	probe->id = tr->count.sent;
	probe->idx = tr->count.sent % tr->opts.nqueries;
	probe->hdx = tr->count.sent / tr->opts.nqueries;
	set_sockttl(tr, hop->ttl);
	probe->daddr.sin_addr = tr->out.daddr.sin_addr;
	probe->daddr.sin_port = htons(probe->port);
	sendto(tr->out.sock, tr->out.packet, tr->opts.packetsize, 0,
		(struct sockaddr*)&(probe->daddr), sizeof(probe->daddr));
	gettimeofday(&(probe->ts), NULL);
	++tr->count.sent;
}
