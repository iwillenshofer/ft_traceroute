/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:28 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 11:23:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** validates the size of the icmp packet and sets the headers shortcuts for use
** in other functions
*/
static t_bool	check_icmp_size(t_ping *ft_ping, t_headers *headers)
{
	size_t		cksum;
	t_msghdr	*msg;
	size_t		size;

	msg = &(ft_ping->in.recv.msg);
	size = ft_ping->in.recv.received;
	headers->ip = msg->msg_iov->iov_base;
	if (size < sizeof(t_ipheader) || size < htons(headers->ip->tot_len)
		|| size < (headers->ip->ihl * 4) + sizeof(t_icmpheader))
	{
		dprintf(STDERR_FILENO,"packet too short\n");
		return (false);
	}
	headers->icmp = (t_icmpheader *)((char *)(headers->ip)
			+ (headers->ip->ihl * 4));
	headers->data = (char *)(headers->icmp) + sizeof(t_icmpheader);
	cksum = headers->ip->check;
	headers->ip->check = 0;
	if (checksum(headers->ip, htons(headers->ip->tot_len))
		!= cksum)
	{
		printf("ip checksum does not match\n");
		return (false);
	}
	return (true);
}

/*
** parses the icmp message to check for failures on size or data.
** assumes a packet of any size has been received and stored in ft_ping->msg,
** as well as ft_ping->received has been set with the number of bytes that were
** received.
*/
static t_bool	prs_icmp(t_ping *ft_ping, t_headers *headers)
{
	if (!check_icmp_size(ft_ping, headers))
		return (false);
	if (ntohs(headers->icmp->un.echo.id) != (unsigned short)(ft_ping->pid))
		return (false);
	if (headers->icmp->type == ICMP_TIME_EXCEEDED)
	{
		ft_ping->in.recv.ttl_exceeded = true;
		return (true);
	}
	if (headers->icmp->type != ICMP_ECHOREPLY)
		return false;
	if (check_duptrack(ft_ping, ntohs(headers->icmp->un.echo.sequence)))
		ft_ping->in.recv.duplicated = true;
	set_duptrack(ft_ping, ntohs(headers->icmp->un.echo.sequence));
	return (true);
}

/*
** initializes the structure ft_ping->in, which will receive the ICMP data
** from recvmsg();
*/
static void		init_receive(t_ping *ft_ping)
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
** Let's print all the pings!!!!
*/
static void	ping_print(t_ping *ft_ping, t_headers *headers)
{
	dprintf(STDOUT_FILENO, "%d bytes from %s: ",
			ntohs(headers->ip->tot_len) - (headers->ip->ihl * 4),
			inet_ntoa(ft_ping->in.recv.peer_addr.sin_addr));
	if (ft_ping->in.recv.ttl_exceeded)
	{
		dprintf(STDOUT_FILENO, "Time to live exceeded\n");
		return ;
	}
	else
		dprintf(STDOUT_FILENO, "icmp_seq=%d ttl=%d", ntohs(headers->icmp->un.echo.sequence), headers->ip->ttl);
	if (ft_ping->in.recv.duplicated)
    	dprintf (STDOUT_FILENO," (DUP!)");
	if (ft_ping->in.time.record)
		dprintf(STDOUT_FILENO, " time=%.3f ms", ft_ping->in.time.current);
	dprintf(STDOUT_FILENO, "\n");
}

/*
** extracts the timestamp of incoming message and, if exists,
** sets time recording.
*/
void	ping_timestamp(t_ping *ft_ping, t_headers *headers)
{
	t_time	now;
	t_time	timestamp;
	double deviation_new;
	double deviation_old;

	ft_ping->in.time.record = false;
	if (headers->ip->tot_len - (headers->ip->ihl * 8) - sizeof(t_icmpheader)
			> sizeof(t_time))
	{
		gettimeofday(&now, NULL);
		ft_memcpy(&timestamp, headers->data, sizeof(t_time));
		timestamp = elapsed_time(timestamp, now);
		ft_ping->in.time.current = (double)(timestamp.tv_sec) * 1000
				+ (double)(timestamp.tv_usec) / 1000;
		ft_ping->in.time.record = true;
		if (ft_ping->in.time.current > ft_ping->in.time.max)
			ft_ping->in.time.max = ft_ping->in.time.current;
		if (ft_ping->in.time.current < ft_ping->in.time.min  || (ft_ping->in.replies == 1))
			ft_ping->in.time.min = ft_ping->in.time.current;
		deviation_old = ft_ping->in.time.current - ft_ping->in.time.avg;
		ft_ping->in.time.avg = ft_ping->in.time.avg
				+ ((ft_ping->in.time.current - ft_ping->in.time.avg) / ft_ping->in.replies);
		deviation_new = ft_ping->in.time.current - ft_ping->in.time.avg;
		ft_ping->in.time.sum_squares = ft_ping->in.time.sum_squares + deviation_old * deviation_new;
		ft_ping->in.time.variance = ft_ping->in.time.sum_squares / ft_ping->in.replies;
	}
}

/*
** receives a message on a nonblocking operation recvmsg(... MSG_DONTWAIT)
** if something came in, we parse it to check if it is our expected ECHO_REPLY
** if it is not what we expected, just drop it, unless it is an error (small packet,
**  duplicated...)
*/
t_bool	ping_in(t_ping *ft_ping)
{
	t_headers	headers;

	init_receive(ft_ping);
	ft_ping->in.recv.received = recvmsg(ft_ping->sock, &(ft_ping->in.recv.msg), MSG_DONTWAIT);
	if (ft_ping->in.recv.received > 0)
	{
		if (prs_icmp(ft_ping, &headers))
		{
			ft_ping->in.count++;
			if (ICMP_ECHOREPLY && !(ft_ping->in.recv.duplicated))
			{
				ft_ping->in.replies++;
				ping_timestamp(ft_ping, &headers);
			}
			ping_print(ft_ping, &headers);
		}
		return (true);
	}
	return (false);
}
