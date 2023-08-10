/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:07:38 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 15:07:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"


/*
** receives the current hop id and check for "future" probes
*/
static double	checkfutureprobe(t_trace *tr, t_probe *p, size_t hid, double t)
{
	size_t	pidx;

	pidx = 0;
	while (pidx < tr->opts.nqueries && tr->hop[hid].probe[pidx].sent)
	{
		if (tr->hop[hid].probe[pidx].received)
		{
			if (hid == p->hdx
				&& (tr->hop[hid].probe[pidx].elapsed * 3 > t || !(t)))
				t = (tr->hop[hid].probe[pidx].elapsed + 1) * 3;
			else if (tr->hop[hid].probe[pidx].elapsed * 10 < t || !(t))
				t = (tr->hop[hid].probe[pidx].elapsed + 1) * 10;
		}
		pidx++;
	}
	return (t);
}

/*
** MAX,HERE,NEAR
** Wait for a probe no more than HERE (default 3)
** times longer than a response from the same hop,
** or no more than NEAR (default 10) times than some
** next hop, or MAX (default 5.0) seconds
*/
t_time	timetowait(t_trace *tr, t_probe *probe)
{
	double	ttw;
	size_t	hidx;

	hidx = probe->hdx;
	ttw = 0.0;
	while (hidx < tr->opts.maxhop)
	{
		ttw = checkfutureprobe(tr, probe, hidx, ttw);
		hidx++;
	}
	if (!ttw)
		ttw = DFL_TIMEOUTMS;
	return (ms_to_time(ttw));
}
