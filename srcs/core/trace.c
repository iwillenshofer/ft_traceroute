/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:42:54 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/07 20:06:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include "errno.h"

#define ERR_BIND "ERR_BIND\n"
#define ERR_SOCKET "ERR_SOCKET\n"

void	trace3(t_trace *tr)
{
	struct sockaddr_in baddr;

	struct sockaddr_in recvaddr;

	static int rec = 0;
	static int seq = 0;
	int ret;
	if (seq < 30)
	{
		set_sockttl(tr, 1);
		ft_bzero(&baddr, sizeof(baddr));
		tr->out.daddr.sin_port = htons(33434 + seq++);
		sendto(tr->out.sock, tr->out.packet, sizeof(tr->opts.packetsize), 0, (struct sockaddr*)&(tr->out.daddr), sizeof(tr->out.daddr));
	}

	ft_bzero(tr->in.buf, sizeof(tr->in.buf));
	errno = 0;
	
	ft_bzero(&recvaddr, sizeof(recvaddr));
	socklen_t len;
	ret = recvfrom(tr->out.sock, tr->in.buf, sizeof(tr->in.buf), MSG_ERRQUEUE | MSG_DONTWAIT, (struct sockaddr *)&(recvaddr), &len);
	if (ret == -1)
	{
		if (errno != 11)
			printf("%d: %s\n", errno, strerror(errno));
	}
	else if (ret > 0)
	{
		dprintf(STDOUT_FILENO, "%s\n", inet_ntoa(recvaddr.sin_addr));	
		ft_puthex_bytes(tr->in.buf, ret, 1, 0);
		rec++;
	}
}











int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;
	unsigned char *v1;
	unsigned char *v2;

	i = 0;
	v1 = (unsigned char *)(s1);
	v2 = (unsigned char *)(s2);
	while (i < n)
	{
		if (v1[i] != v2[i])
			return (v2[i] - v1[i]);
		i++;
	}
	return (0);
}


static void print_icmp (t_icmp *icmp)
{
	dprintf (STDOUT_FILENO,
		"ICMP: type %u, code %u, id 0x%04x, seq 0x%04x\n",
		icmp->type, icmp->code,
		ntohs(icmp->un.echo.id), ntohs(icmp->un.echo.sequence));
}

static void	print_ip(t_ip *ip)
{
	dprintf(STDOUT_FILENO,
		"Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	dprintf(STDOUT_FILENO,
		" %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x ",
		ip->version, ip->ihl, ip->tos, ntohs(ip->tot_len), ntohs(ip->id),
		(ntohs(ip->frag_off) & 0b1110000000000000) >> 13,
		ntohs(ip->frag_off) & 0b0000111111111111,
		ip->ttl, ip->protocol, ntohs(ip->check));
	dprintf(STDOUT_FILENO, "%s  ",
		inet_ntoa(*(t_inaddr *)(&(ip->saddr))));
	dprintf(STDOUT_FILENO, "%s ",
		inet_ntoa(*(t_inaddr *)(&(ip->daddr))));
	if (ip->ihl * 4 > sizeof(t_ip))
		ft_puthex_bytes(((char *)ip) + sizeof(t_ip),
			(ip->ihl * 4) - sizeof(t_ip), 0, 0);
	dprintf(STDOUT_FILENO, "\n");
}

static void	print_udp(t_udp *udp)
{
	dprintf(STDOUT_FILENO,
		"src_port dst_port dgram_len dgram_cksum\n");
	dprintf(STDOUT_FILENO,
		" %u %u %02x %02x\n",
		ntohs(udp->source),
		ntohs(udp->dest),
		ntohs(udp->len),
		ntohs(udp->check));
}

void	trace(t_trace *tr)
{
	struct sockaddr_in baddr;

	static int rec = 0;
	static int seq = 0;
	int ret;
	if (seq < 30 && !(tr->done))
	{
		set_sockttl(tr, seq + 1);
		ft_bzero(&baddr, sizeof(baddr));
		tr->out.daddr.sin_port = htons(33434 + seq++);
		sendto(tr->out.sock, tr->out.packet, sizeof(tr->opts.packetsize), 0, (struct sockaddr*)&(tr->out.daddr), sizeof(tr->out.daddr));
	}

	struct sockaddr_in recvaddr;
	socklen_t len;
	ft_bzero(tr->in.buf, sizeof(tr->in.buf));
	ret = recvfrom(tr->in.sock, tr->in.buf, sizeof(tr->in.buf), MSG_DONTWAIT, (struct sockaddr*)&(recvaddr), &len);
	if (ret > 0)
	{
		
		//if (!(ft_memcmp(&(recvaddr.sin_addr.s_addr), &(tr->out.daddr.sin_addr), sizeof(tr->out.daddr.sin_addr))))
		//tr->done = true;


		t_ip *ip = (t_ip*)tr->in.buf;
		t_icmp *icmp = (t_icmp*)(ip + 1);
		t_ip *oip = (t_ip*)(icmp + 1);
		t_udp *oudp = (t_udp*)(oip + 1);
//		printf("ICMP type: %d, code: %d\n", icmp->type, icmp->code);
		printf("%d: %s\n", oip->ttl, inet_ntoa(recvaddr.sin_addr));
		print_icmp(icmp);
		print_ip(oip);
		print_udp(oudp);
//		ft_puthex_bytes(tr->in.buf, ret, 1, 0);
		rec++;
	}
	if (rec > 10)
		tr->done = true;
}


t_probe *getprobe(t_trace *tr, in_port_t port)
{
	size_t				i;
	size_t				j;

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
	if (hop->probe[probeidx].sent && hop->probe[probeidx].received)
	{
		if (!probeidx)
			dprintf(STDOUT_FILENO, "%lu: ", hop->ttl);
		dprintf(STDOUT_FILENO, " %.3f ms ", elapsed_time_ms(hop->probe[probeidx].ts, hop->probe[probeidx].tr));
		if (probeidx == tr->opts.nqueries - 1)
			dprintf(STDOUT_FILENO, "\n");
		tr->curr_prt++;
		if (probeidx == tr->opts.nqueries - 1 && hop->lasthop)
			tr->done = true;
	}
	else if (hop->probe[probeidx].sent && timed_out(hop->probe[probeidx].ts, tr->opts.timeout))
	{
		if (!probeidx)
			dprintf(STDOUT_FILENO, "%lu: ", hop->ttl);
		dprintf(STDOUT_FILENO, " * ");
		if (probeidx == tr->opts.nqueries - 1)
			dprintf(STDOUT_FILENO, "\n");
		hop->probe[probeidx].received = true;
		tr->count.recv++;
		tr->curr_prt++;
		if (probeidx == tr->opts.nqueries - 1 && hop->lasthop)
			tr->done = true;
	}
	if (tr->curr_prt == tr->opts.nqueries * tr->opts.maxhop)
		tr->done = true;
}


void	recvpackets(t_trace *tr)
{
	size_t				i; (void)i;
	t_probe				*probe;	(void)probe;
	int					ret;

	probe = NULL;
	ft_bzero(tr->in.buf, sizeof(tr->in.buf));
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


//		dprintf(STDOUT_FILENO, "\n-----------------\n");
//		dprintf(STDOUT_FILENO, "recv ttl: %u. sport: %u. dport: %u.\n", oip->ttl,ntohs(oudp->source) , ntohs(oudp->dest));
//		print_ip(ip);
//		print_icmp(icmp);
//		print_ip(oip);
//		print_udp(oudp);
//		dprintf(STDOUT_FILENO, "-----------------\n");
		probe = getprobe(tr, ntohs(oudp->dest));
		if (probe && !(probe->received))
		{
			gettimeofday(&(probe->tr), NULL);
			probe->received = true;
			ft_memcpy(&(probe->icmp), icmp, sizeof(probe->icmp));
			tr->count.recv++;
		}	
//		printf("ICMP type: %d, code: %d\n", icmp->type, icmp->code);
//		printf("%d: %s\n", oip->ttl, inet_ntoa(tr->in.saddr.sin_addr));
//		print_icmp(icmp);
//		print_ip(oip);
//		print_udp(oudp);
//		ft_puthex_bytes(tr->in.buf, ret, 1, 0);
	}
}

/*
** just to make it clear: A packet is marked as received either
** if we've got it, or if it timed out.
*/
#include <errno.h>
void	sendpackets(t_trace *tr)
{
	size_t			i;
	t_hop			*hop;
	t_probe			*probe;	
	static size_t	sent = 0;

	i = 0;
	if (sent > tr->count.recv)
		return ;
	while (i < tr->opts.squeries && sent < tr->opts.nqueries * tr->opts.maxhop)
	{
		hop = &(tr->hop[sent / tr->opts.nqueries]);
		probe = &(hop->probe[sent % tr->opts.nqueries]);
		hop->ttl = sent / tr->opts.nqueries + 1;
		probe->port = DFL_STARTPORT + sent;
		probe->sent = true;
		probe->id = sent % tr->opts.nqueries;
		gettimeofday(&(probe->ts), NULL);
		set_sockttl(tr, hop->ttl);
		tr->out.daddr.sin_port = htons(probe->port);
		if (sendto(tr->out.sock, tr->out.packet, sizeof(tr->opts.packetsize), 0, (struct sockaddr*)&(tr->out.daddr), sizeof(tr->out.daddr)) == -1)
		{	
			dprintf(STDOUT_FILENO, "SEND ERROR: %s\n", strerror(errno));
			dprintf(STDOUT_FILENO, "hop[%lu] probe[%lu]: p:%u \n", hop->ttl, probe->id, probe->port);
		}
		
		tr->count.sent = ++sent;
		i++;
	}
//	i = 0;
//	size_t j = 0;
//	while (i < tr->opts.maxhop)
//	{
//		dprintf(STDOUT_FILENO, "HOP[%lu]: ttl: %lu", i, tr->hop[i].ttl);
//		j = 0;
//		while (j < tr->opts.nqueries)
//		{
//			dprintf(STDOUT_FILENO, " probe[%lu]: s:%u r:%u p:%u ", j, tr->hop[i].probe[j].sent, tr->hop[i].probe[j].received, tr->hop[i].probe[j].port);
//			j++;
//		}
//		dprintf(STDOUT_FILENO, "\n");
//		i++;
//	}
}

/*
** this is the main function...
** strategy:
** we'll use a custom timeout and set reading operation to DONT WAIT instead of a select()
** 1. will sent a bunch of packets (16 by default)
** 2. will always listen
** 3. will try to print result, checking if it is marked as received (until timeout);
**    - if result is not received and timeout is expired, just print '*' and set it as received.
** 4. will send another bunch of packets IF all the previous ones are marked as received (either from real receipt or by timeout)
*/
void	traceroute(t_trace *tr)
{
	while (!(tr->done))
	{
		sendpackets(tr);
		recvpackets(tr);
		prntpackets(tr);
		usleep(500);
	}
}
