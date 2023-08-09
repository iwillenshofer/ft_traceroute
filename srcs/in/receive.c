/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:58:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 01:03:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static t_probe *getprobe(t_trace *tr, in_port_t port)
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

void	recvpackets(t_trace *tr)
{
	t_probe				*probe;
	int					ret;

	probe = NULL;
	ft_bzero(&tr->in.saddr, sizeof(tr->in.saddr));
	ret = recvfrom(tr->in.sock, tr->in.buf, sizeof(tr->in.buf), MSG_DONTWAIT, (struct sockaddr*)&(tr->in.saddr), &tr->in.saddrlen);
	if (ret > 0)
	{
		//the whole work now will be checking if this is a valid ICMP packet.... we'll ignore it validation for now
		//and assume the packet is valid... 
		t_ip *ip = (t_ip*)tr->in.buf;
		t_icmp *icmp = (t_icmp*)(ip + 1);
		t_ip *oip = (t_ip*)(icmp + 1);
		t_udp *oudp = (t_udp*)(oip + 1);
		probe = getprobe(tr, ntohs(oudp->dest));
		if (probe && !(probe->received))// && probe->id <= tr->curr_prt)
		{
			gettimeofday(&(probe->tr), NULL);
			probe->elapsed = elapsed_time_ms(probe->ts, probe->tr);
			probe->received = true;
			ft_bzero(&probe->saddr, sizeof(probe->saddr));
			probe->saddr.sin_family = AF_INET;
			probe->saddr.sin_addr = *(struct in_addr*)&(ip->saddr);
			if (!ft_memcmp(&probe->daddr.sin_addr, &ip->saddr, sizeof(in_addr_t)))
				tr->hop[probe->hdx].lasthop = true;
			tr->count.recv++;
		}
	}
}
