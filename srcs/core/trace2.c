/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:09:36 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/04 12:28:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <errno.h>
void	probe(t_trace *tr)
{
	t_hop *hop;
	t_probe *probe;


	hop = &(tr->hop[tr->count.sent / tr->opts.nqueries]);
	probe = &(hop->probe[tr->count.sent % tr->opts.nqueries]);
	ft_memcpy(&(probe->daddr), &(tr->out.daddr), sizeof(probe->daddr));
	hop->id = tr->count.sent / tr->opts.nqueries;
	probe->daddr.sin_port = htons(tr->opts.port + tr->count.sent);
	probe->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	probe->bindaddr.sin_port = 0;//htons(tr->opts.port + tr->count.sent);
	probe->bindaddr.sin_family = AF_INET;
	probe->bindaddr.sin_addr.s_addr = INADDR_ANY;
	/*
	** we'll set TTL here
	*/

	if (probe->sock == -1)
		prs_fatal(tr, "SOCKET ERROR\n", NULL, false);

	t_bool n = true;
	    if (setsockopt (probe->sock, SOL_IP, IP_RECVERR, &n, sizeof (n)) < 0)
		    prs_fatal (tr, "setsockopt IP_RECVERR", NULL, false);
		if (setsockopt (probe->sock, SOL_IP, IP_RECVTTL, &n, sizeof (n)) < 0)
		    prs_fatal (tr, "setsockopt IP_RECVTTL", NULL, false);
		if (setsockopt (probe->sock, SOL_SOCKET, SO_TIMESTAMP, &n, sizeof (n)) < 0)
		    prs_fatal (tr, "setsockopt SO_TIMESTAMP", NULL, false);

		int z = 3;
		if (setsockopt (probe->sock, SOL_IP, IP_TTL, &(z), sizeof (z)) < 0)
		    prs_fatal(tr, "setsockopt IP_TTL", NULL, false);

		printf("BINDING addr: %s, port: %u, family: %u.\n",
			inet_ntoa(probe->bindaddr.sin_addr),
			ntohs(probe->bindaddr.sin_port),
			probe->bindaddr.sin_family
			);
	if (bind(probe->sock, (struct sockaddr *)&(probe->bindaddr), sizeof(probe->bindaddr)) == -1)
	{

		printf("%s\n", strerror(errno));
		prs_fatal(tr, "BINDING ERROR\n", NULL, false);
	}

		printf("SENDING addr: %s, port: %u, family: %u.\n",
			inet_ntoa(probe->daddr.sin_addr),
			ntohs(probe->daddr.sin_port),
			probe->daddr.sin_family
			);

	if (sendto(probe->sock, tr->out.packet, tr->opts.packetsize,0,(struct sockaddr *)&(probe->daddr), sizeof(probe->daddr)) == -1)
		prs_fatal(tr, "SENDING ERROR\n", NULL, false);
//     int ret_val = recvfrom(probe->sock, tr->in.buf, sizeof(tr->in.buf), 0, NULL, NULL);
//     if (ret_val != -1) {
//         printf("Received data (len %d bytes): %s\n", ret_val, tr->in.buf);
//     } else {
//         printf("recvfrom() failed [%s]\n", strerror(errno));
//     }
	probe->sent = true;
	tr->count.sent++;
	FD_SET(probe->sock, &(tr->readfds));
	FD_SET(probe->sock, &(tr->errfds));
	gettimeofday(&(probe->ts), NULL);
}

void	send_probes(t_trace *tr)
{
	size_t i;

	i = 0;
	while (i < tr->opts.squeries && tr->count.sent <  tr->opts.nqueries * tr->opts.maxhop)
	{
		printf("probing hop: %lu, probe: %lu\n", tr->count.sent / tr->opts.nqueries, tr->count.sent % tr->opts.nqueries);
		probe(tr);
		i++;
	}
}

int get_max_fd(t_trace *tr)
{
	size_t i;
	t_hop *hop;
	t_probe *probe;
	int max;

	i = 0;
	max = 0;
	while (i < tr->count.sent)
	{
		hop = &(tr->hop[i / tr->opts.nqueries]);
		probe = &(hop->probe[i % tr->opts.nqueries]);
		if (probe->sock > max && probe->sock && !(probe->received))
			max = probe->sock;
	//	printf("[%d] ", probe->sock);
		i++;
	}
	if (i)
		max++;
	//printf("\nMAX FDS: %d\n", max);
	return (max);
}

void	receive_probes(t_trace *tr)
{
	int ret;
	//t_time	timeout;
	//timeout.tv_sec = 0;
	//timeout.tv_usec = 100000;
	struct sockaddr_in recvaddr; 
	socklen_t len;
	struct sockaddr_in sendaddr; 

	ft_bzero(&sendaddr, sizeof(sendaddr));
	sendaddr.sin_addr.s_addr = htonl((127 << 24) + 1);
	
	
	if (sendto(tr->in.sock, tr->out.packet,
				sizeof(t_icmp) + 50, 0,
				(struct sockaddr *)&(sendaddr),
				sizeof(struct sockaddr)) <= 0)
		printf("SENDING ERROR: %s\n", strerror(errno));
	printf("sent\n");
	FD_ZERO(&(tr->readfds));
	FD_SET(tr->in.sock, &(tr->readfds));
	errno = 0;
	(void)ret;
	ret = recvfrom(tr->in.sock, tr->in.buf, MSG_WAITALL, sizeof(tr->in.buf), (struct sockaddr*)&(recvaddr), &(len));
//	if (ret < 0)
//		printf("RECEIVING ERROR: %s\n", strerror(errno));
//	else
	if (ret > 0)
		printf("GOT SOMETHING\n");
	FD_CLR(tr->in.sock, &(tr->readfds));
//			printf("this probe is set: h[%ld] p[%ld] rcv: %d, err[%u]\n", i / tr->opts.nqueries, i % tr->opts.nqueries, ret, FD_ISSET(probe->sock, &(tr->errfds)));
//			gettimeofday(&(probe->tr), NULL);

}

t_bool	done(t_trace *tr, t_bool sending)
{
	if (sending && tr->count.sent >=  tr->opts.nqueries * tr->opts.maxhop)
		return (true);
	if (tr->count.recv >= tr->count.sent && tr->count.sent >= tr->opts.nqueries * tr->opts.maxhop)
		return (true);
	return (false);
}

int closeallsockets(t_trace *tr)
{
	size_t i;
	t_hop *hop;
	t_probe *probe;
	int max;

	i = 0;
	max = 0;
	while (i < tr->count.sent)
	{
		hop = &(tr->hop[i / tr->opts.nqueries]);
		probe = &(hop->probe[i % tr->opts.nqueries]);
		if (probe->sock)
			close(probe->sock);
		probe->sock = 0;
		i++;
	}
	max++;
	return (max);
}

int printallprobes(t_trace *tr)
{
	size_t i;
	t_hop *hop;
	t_probe *probe;
	int max;

	i = 0;
	max = 0;
	while (i < (tr->opts.nqueries * tr->opts.maxhop))
	{
		hop = &(tr->hop[i / tr->opts.nqueries]);
		probe = &(hop->probe[i % tr->opts.nqueries]);
		dprintf(STDOUT_FILENO, "hop[%lu], probe[%lu], rec[%c], time=%.3f ms\n",
			i / tr->opts.nqueries,
			i % tr->opts.nqueries,
			probe->received ? 'X' : ' ',
			elapsed_time_ms(probe->ts, probe->tr));
		i++;
	}
	max++;
	return (max);
}

void	trace(t_trace *tr)
{
	printf("traceroute to %s (%s), %lu hops max, %lu byte packets\n",
		tr->out.host, 
		inet_ntoa(tr->out.daddr.sin_addr),
		tr->opts.maxhop, tr->opts.packetsize + sizeof(t_ip) + sizeof(t_udp));
	while (!done(tr, false))
	{
		(void)tr;
		receive_probes(tr);
		if (!done(tr, true))
		{
		//	send_probes(tr);
		//	sleep(1);
		}
	}
	closeallsockets(tr);
	printallprobes(tr);
}
