/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:01:19 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 15:54:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** gets the last valid address of a hop, up to the current probe
** if there is none, returnes a zeroed address
*/
static struct sockaddr_in	lastaddr(t_trace *tr, t_probe *probe)
{
	struct sockaddr_in	ret;
	size_t				idx;

	ft_bzero(&ret, sizeof(ret));
	if (!probe->idx)
		return (ret);
	idx = 0;
	while (idx < probe->idx)
	{
		if (tr->hop[probe->hdx].probe[idx].received)
			ret = tr->hop[probe->hdx].probe[idx].saddr;
		idx++;
	}
	return (ret);
}

static void prnttimedout(t_trace *tr, t_hop *hop, size_t probeidx)
{
	color(tr, PURPLE, BOLD);
	dprintf(STDOUT_FILENO, " *");
	color(tr, RESET, REGULAR);
	hop->probe[probeidx].timedout = true;
	tr->count.timedout++;
}

/*
** prints a valid timed packet
*/
static void	prntvalid(t_trace *tr, t_hop *hop, size_t probeidx)
{
	struct sockaddr_in	last;
	struct sockaddr_in	addr;

	addr = hop->probe[probeidx].saddr;
	last = lastaddr(tr, &(hop->probe[probeidx]));
	if (ft_memcmp(&addr.sin_addr, &last.sin_addr, sizeof(struct in_addr)))
	{
		color(tr, CYAN, BOLD);
		if (tr->opts.nodns)
			dprintf(STDOUT_FILENO, " %s", inet_ntoa(addr.sin_addr));
		else
		{
			dprintf(STDOUT_FILENO, " %s", fqdn(tr, &addr));
			color(tr, CYAN, FAINT);
			dprintf(STDOUT_FILENO, " (%s)", inet_ntoa(addr.sin_addr));
		}
	}
	color(tr, WHITE, BOLD);
	dprintf(STDOUT_FILENO, "  %.3f", hop->probe[probeidx].elapsed);
	color(tr, WHITE, FAINT);
	dprintf(STDOUT_FILENO, " ms");
	color(tr, RESET, REGULAR);
	print_icmperror(&(hop->probe[probeidx].headers.icmp));
}

/*
** now, we will start printing our packets.
** also, if we reach timeout or the ICMP code is not TTL, we will make it as
** received and print an '*'.
** also, will check if it is done (when the last packet is either received or
** timedout)
*/
void	prntpackets(t_trace *tr)
{
	t_hop	*hop;
	size_t	probeidx;

	hop = &(tr->hop[tr->count.prt / tr->opts.nqueries]);
	probeidx = tr->count.prt % tr->opts.nqueries;
	if (hop->probe[probeidx].sent && (hop->probe[probeidx].received
			|| timed_out(hop->probe[probeidx].ts,
				timetowait(tr, &hop->probe[probeidx]))))
	{
		if (!probeidx)
		{
			color(tr, WHITE, BOLD);
			dprintf(STDOUT_FILENO, "%2lu ", hop->ttl);
		}
		if (hop->probe[probeidx].received)
			prntvalid(tr, hop, probeidx);
		else
			prnttimedout(tr, hop, probeidx);
		if (probeidx == tr->opts.nqueries - 1)
			dprintf(STDOUT_FILENO, "\n");
		tr->count.prt++;
		if ((probeidx == tr->opts.nqueries - 1 && hop->lasthop)
			|| tr->count.prt == (tr->opts.nqueries * tr->opts.maxhop))
			tr->done = true;
	}
}
