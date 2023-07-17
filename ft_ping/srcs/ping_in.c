/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:28 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/17 09:08:23 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


int check_icmp_size(t_ping *ft_ping, t_msghdr *msg, size_t size)
{
	t_ipheader *ip;

	ip = msg->msg_iov->iov_base;
	printf("we are parsing %zu. ipheader: %zu. tot_len: %d. tot_headers: %zu\n", size, sizeof(t_ipheader), htons(ip->tot_len), (ip->ihl * 4) + sizeof(t_icmpheader));
	if (size < sizeof(t_ipheader) || size < htons(ip->tot_len)
		|| size < (ip->ihl * 4) + sizeof(t_icmpheader))
		return (false);
	if (calculate_checksum(ip, htons(ip->tot_len)))
	{
		printf("checksum does not match\n");
		return (false);
	}
	else
	{
		printf("checksum matches\n");
	}
	(void)ft_ping;
	return (true);
}

t_bool parse_icmp(t_ping *ft_ping, t_msghdr *msg, size_t size, t_headers *headers)
{
	if (!check_icmp_size(ft_ping, msg, size))
		return (false);
	headers->ip = msg->msg_iov->iov_base;
	headers->icmp = (t_icmpheader *)((char*)(headers->ip) + headers->ip->ihl * 4);
	return (true);
}

/*
** initializes the structure ft_ping->in, which will receive the ICMP data
** from recvmsg();
*/
void init_receive(t_ping *ft_ping)
{
	ft_bzero(&(ft_ping->in), sizeof(t_receive));
	ft_ping->in.msg.msg_name = &(ft_ping->in.peer_addr);
	ft_ping->in.msg.msg_namelen = sizeof(struct sockaddr_in);
	ft_ping->in.msg.msg_iov = &(ft_ping->in.iobuf);
	ft_ping->in.msg.msg_iovlen = 1;
	ft_ping->in.msg.msg_iov->iov_base = ft_ping->in.buf;
	ft_ping->in.msg.msg_iov->iov_len = sizeof(ft_ping->in.buf);
}

t_bool ping_in(t_ping *ft_ping)
{
	//bytes_ind = recvfrom(ft_ping->sock, &buf, sizeof(buf), MSG_DONTWAIT, (struct sockaddr*)&peerAddr, &len);
	init_receive(ft_ping);
	ft_ping->in.received = recvmsg(ft_ping->sock, &(ft_ping->in.msg), MSG_DONTWAIT);
	if (ft_ping->in.received > 0)
	{
		/* now we gotta learn how to interpret this header*/
		/* what do we in back form it? just the data? a icmp header?*/
		/* so, as always, let's print it */
		printf("ICMP packet ind from %s\n", qualified_address(ft_ping, &(ft_ping->in.peer_addr.sin_addr)));
	//	ft_puthex_bytes(msg.msg_name, msg.msg_namelen);
	//	ft_puthex_bytes(msg.msg_iov->iov_base, msg.msg_iov->iov_len);

		/* cool. we in IP + ICMP + DATA header in our buffer*/
		/* we will just check if those headers are valid*/
		t_headers headers;
		if (parse_icmp(ft_ping, &(ft_ping->in.msg), (size_t)ft_ping->in.received, &headers))
		{
			printf("parsing successfull\n");
			ft_puthex_bytes(headers.ip, sizeof(t_ipheader));
			ft_puthex_bytes(headers.icmp, sizeof(t_icmpheader));
			ft_puthex_bytes((char *)(headers.icmp) + sizeof(t_icmpheader) , htons(headers.ip->tot_len) -  sizeof(t_icmpheader));
		}

//		int ihl = ((t_ipheader *)buf)->ihl;
		return (1);
	}
	else
		return (0);

}
