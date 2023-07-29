/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:28 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 21:23:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** validates the size of the icmp packet and sets the headers shortcuts for use
**  in other functions.
** If checksum is invalid, prints message. If size is too small for icmp
**  packet, just drop it.
*/

static t_bool	parse_icmp(t_ping *ft_ping)
{
	size_t		cksum;
	size_t		size;
	t_headers	*hdrs;

	hdrs = &(ft_ping->in.recv.hdrs);
	size = ft_ping->in.recv.received;
	hdrs->ip = ft_ping->in.recv.msg.msg_iov->iov_base;
	if (size < sizeof(t_ip) || size < htons(hdrs->ip->tot_len)
		|| size < (hdrs->ip->ihl * 4) + sizeof(t_icmp))
	{
		dprintf(STDERR_FILENO, "packet too short (%lu bytes) from %s\n", size,
			inet_ntoa (*(t_inaddr *)(&(hdrs->ip->saddr))));
		return (false);
	}
	hdrs->icmp = (t_icmp *)((char *)(hdrs->ip) + (hdrs->ip->ihl * 4));
	if (hdrs->icmp->type == ICMP_ECHO)
		return (false);
	ft_ping->in.recv.hdrs.data = (char *)(hdrs->icmp) + sizeof(t_icmp);
	cksum = hdrs->icmp->checksum;
	hdrs->icmp->checksum = 0;
	hdrs->datalen = htons(hdrs->ip->tot_len)
		- (hdrs->ip->ihl * 4) - sizeof(t_icmp);
	if (checksum(hdrs->icmp, hdrs->datalen + sizeof(t_icmp)) != cksum)
		dprintf(STDERR_FILENO, "checksum mismatch from %s\n",
			inet_ntoa(*(t_inaddr *)(&(hdrs->ip->saddr))));
	return (true);
}

/*
** parses the icmp message to check for failures on size or data.
** assumes a packet of any size has been received and stored in ft_ping->msg,
** as well as ft_ping->received has been set with the number of bytes that were
** received.
** all packets that are returned (false) are dropped.
*/
static t_bool	check_icmp(t_ping *ft_ping)
{
	if (ft_ping->in.recv.hdrs.icmp->type != ICMP_ECHOREPLY
		&& ft_ping->in.recv.hdrs.icmp->type != ICMP_TIMESTAMPREPLY
		&& ft_ping->in.recv.hdrs.icmp->type != ICMP_ADDRESSREPLY)
	{
		icmp_noecho(ft_ping);
		return (false);
	}
	if ((ft_ping->in.recv.hdrs.icmp->un.echo.id) != htons(ft_ping->pid))
		return (false);
	if (check_duptrack(ft_ping,
			ntohs(ft_ping->in.recv.hdrs.icmp->un.echo.sequence)))
	{
		ft_ping->in.count.dup++;
		ft_ping->in.recv.duplicated = true;
	}
	set_duptrack(ft_ping, ntohs(ft_ping->in.recv.hdrs.icmp->un.echo.sequence));
	return (true);
}

/*
** extracts the timestamp of incoming message and, if exists,
** sets time recording.
*/
void	ping_timestamp(t_ping *ft_ping)
{
	double	deviation_new;
	double	deviation_old;
	t_time arrived;

	ft_memcpy(&arrived, ft_ping->in.recv.hdrs.data, sizeof(t_time));
	if (ft_ping->in.recv.hdrs.datalen > sizeof(t_time))
	{
		ft_ping->in.count.timed++;
		ft_ping->in.time.current
			= elapsed_time_ms(arrived, ft_ping->in.time.now);
		if (ft_ping->in.time.current > ft_ping->in.time.max)
			ft_ping->in.time.max = ft_ping->in.time.current;
		if (ft_ping->in.time.current < ft_ping->in.time.min
			|| (ft_ping->in.count.timed == 1))
			ft_ping->in.time.min = ft_ping->in.time.current;
		deviation_old = ft_ping->in.time.current - ft_ping->in.time.avg;
		ft_ping->in.time.avg = ft_ping->in.time.avg
			+ ((ft_ping->in.time.current - ft_ping->in.time.avg)
				/ ft_ping->in.count.timed);
		deviation_new = ft_ping->in.time.current - ft_ping->in.time.avg;
		ft_ping->in.time.sum_squares = ft_ping->in.time.sum_squares
			+ deviation_old * deviation_new;
		ft_ping->in.time.variance = ft_ping->in.time.sum_squares
			/ ft_ping->in.count.timed;
	}
}

/*
** initializes the structure ft_ping->in, which will receive the ICMP data
** from recvmsg();
*/
static void	init_receive(t_ping *ft_ping)
{
	ft_bzero(&(ft_ping->in.recv), sizeof(t_receive));
	ft_ping->in.recv.msg.msg_name = &(ft_ping->in.recv.peer_addr);
	ft_ping->in.recv.msg.msg_namelen = sizeof(struct sockaddr_in);
	ft_ping->in.recv.msg.msg_iov = &(ft_ping->in.recv.iobuf);
	ft_ping->in.recv.msg.msg_iovlen = 1;
	ft_ping->in.recv.msg.msg_iov->iov_base = ft_ping->in.recv.buf;
	ft_ping->in.recv.msg.msg_iov->iov_len = sizeof(ft_ping->in.recv.buf);
}

/*
** receives a message on a nonblocking operation recvmsg(... MSG_DONTWAIT)
** if something came in, we parse it to check if it is our expected ECHO_REPLY
** if it is not what we expected, just drop it, unless it is an error (small
packet, duplicated...)
**
** The flow is as follows:
** 1. parse the icmp packet. Any problem with the packet itself is threated 
**  there.
** 2. Then, checks if it is a valid reply, by check_icmp. Threat invalid
**  replies there.
** 3. If all goes well, check if ping has timestamp, and prints it. If not,
**  prs_icmp has already taken care of it.
*/
t_bool	ping_in(t_ping *ft_ping)
{
	init_receive(ft_ping);
	ft_ping->in.recv.received
		= recvmsg(ft_ping->sock, &(ft_ping->in.recv.msg), MSG_DONTWAIT);
	if (ft_ping->in.recv.received > 0)
	{
		gettimeofday(&(ft_ping->in.time.now), NULL);
		if (parse_icmp(ft_ping) && check_icmp(ft_ping))
		{
			ft_ping->in.count.total++;
			ping_timestamp(ft_ping);
			if (!(ft_ping->options.flood) && !(ft_ping->options.quiet))
				print_echo(ft_ping);
			else if (!(ft_ping->options.quiet))
				ft_putchar('\b');
			return (true);
		}
	}
	return (false);
}
