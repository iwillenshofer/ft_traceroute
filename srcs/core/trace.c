/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:42:54 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/04 20:25:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include "errno.h"
void	trace(t_trace *tr)
{
	int ret;
	//t_bool enabled = true;
	char packet[60];
	ft_bzero(&packet, sizeof(packet));
	//t_ip *ip = (t_ip *)packet;
	//t_udp *udp = (t_udp *)(packet + sizeof(t_ip));
	int val = 1; int ttl = 5;

	struct sockaddr_in daddr;
	ft_bzero(&daddr, sizeof(daddr));
	daddr.sin_family = AF_INET;
	daddr.sin_port = 5001;
	daddr.sin_addr.s_addr = inet_addr("172.217.16.142");


	printf("trying to send\n");
	if((ret = sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&(daddr), sizeof(daddr))) < 0)
		prs_fatal(tr, "could not send\n", NULL, false);

	struct sockaddr_in baddr;
	baddr.sin_family = AF_INET;
	baddr.sin_port = 5001;
	baddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	bind(sock, (struct sockaddr*)&baddr, sizeof(baddr));


	printf("trying to receive\n");
	ft_bzero(tr->in.buf, sizeof(tr->in.buf));
	if ((ret = recvfrom(sock, tr->in.buf, sizeof(tr->in.buf), 0, NULL, NULL)) < 0)
	{
		ft_puthex_bytes(tr->in.buf, sizeof(struct sock_extended_err), 0, 0);
		printf("we got an error\n");
	}
	if (ret > 0)
		ft_puthex_bytes(tr->in.buf, sizeof(tr->in.buf), 1, 0);
	else
		printf("ret = 0\n");
	close(sock);
}
