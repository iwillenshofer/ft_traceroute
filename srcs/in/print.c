/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:01:19 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 01:08:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** MAX,HERE,NEAR
** Wait for a probe no more than HERE (default 3)
** times longer than a response from the same hop,
** or no more than NEAR (default 10) times than some
** next hop, or MAX (default 5.0) seconds (float
** point values allowed too)
*/
static t_time	timetowait(t_trace *tr, t_hop *hop, t_bool print)
{
	double ttw;
	size_t hidx;
	size_t pidx;

	hidx = hop->id;
	ttw = 0.0;
	while (hidx < tr->opts.maxhop)
	{
		pidx = 0;
		while (pidx < tr->opts.nqueries && tr->hop[hidx].probe[pidx].sent)
		{
			if (tr->hop[hidx].probe[pidx].received && tr->hop[hidx].probe[pidx].elapsed)
			{
				if (hidx == hop->id && (tr->hop[hidx].probe[pidx].elapsed * 3 < ttw || !(ttw)))
					ttw = (tr->hop[hidx].probe[pidx].elapsed + 1) * 3;
				else if (tr->hop[hidx].probe[pidx].elapsed * 10 < ttw || !(ttw))
					ttw = (tr->hop[hidx].probe[pidx].elapsed + 1) * 10;
			}
			pidx++;
		}
		hidx++;
	}
	if (!ttw)
		ttw = 5000;
	(void)print;
	return (ms_to_time(ttw));
}

/*
** gets the last valid address of a hop, up to the current probe
** if there is none, returnes a zeroed address
*/
static struct sockaddr_in lastaddr(t_trace *tr, t_probe *probe)
{
	struct sockaddr_in ret;
	size_t	idx;

	ft_bzero(&ret, sizeof(ret));
	if (!probe->idx)
		return (ret);
	idx = 0;

	while (idx < probe->idx)
	{
		if (tr->hop[probe->hdx].probe[idx].received && tr->hop[probe->hdx].probe[idx].elapsed) /* maybe change this to timedout */
			ret = tr->hop[probe->hdx].probe[idx].saddr;
		idx++;
	}
	return (ret);
}

/*
** now, we will start printing our packets.
** also, if we reach timeout or the ICMP code is not TTL, we will make it as
** received and print an '*'.
** also, will check if it is done (when the last packet is either received or timedout)
*/
void	prntpackets(t_trace *tr)
{
	t_hop *hop;
	size_t	probeidx;

	hop = &(tr->hop[tr->curr_prt / tr->opts.nqueries]);
	probeidx = tr->curr_prt % tr->opts.nqueries;
	if (hop->probe[probeidx].sent && (hop->probe[probeidx].received || timed_out(hop->probe[probeidx].ts, timetowait(tr, hop, false))))
	{
		if (!probeidx)
			dprintf(STDOUT_FILENO, "%2lu ", hop->ttl);
		if (hop->probe[probeidx].received)
		{
			struct sockaddr_in last = lastaddr(tr, &(hop->probe[probeidx]));
			if (ft_memcmp(&hop->probe[probeidx].saddr.sin_addr, &last.sin_addr, sizeof(struct in_addr)))
				dprintf(STDOUT_FILENO, " %s (%s)", fqdn(tr, &hop->probe[probeidx].saddr), inet_ntoa(hop->probe[probeidx].saddr.sin_addr));
			dprintf(STDOUT_FILENO, "  %.3f ms", hop->probe[probeidx].elapsed);
		}
		else
		{
			dprintf(STDOUT_FILENO, " *");
			hop->probe[probeidx].received = true;
			tr->count.recv++;
		}
		if (probeidx == tr->opts.nqueries - 1)
			dprintf(STDOUT_FILENO, "\n");
		if ((probeidx == tr->opts.nqueries - 1 && hop->lasthop) || tr->curr_prt == (tr->opts.nqueries * tr->opts.maxhop))
			tr->done = true;
		tr->curr_prt++;
	}
}
