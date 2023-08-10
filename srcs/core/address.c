/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:52:05 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 23:09:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <limits.h>

/*
**	sockaddr is a generic structure. Can be converted to sockaddr_in,
**	sockaddr_in6, sockaddr_un, and so on... Since we are using IPV4,
**	we will deal with it as sockaddr_in using a cast.
**
**	struct sockaddr_in {
**		short            sin_family;   // e.g. AF_INET
**		unsigned short   sin_port;     // e.g. htons(3490)
**		t_inaddr  		 sin_addr;     // see t_inaddr, below
**		char             sin_zero[8];  // zero this if you want to
**	};
**
**	t_inaddr {
**		unsigned long s_addr;  // load with inet_aton()
**	};
*/

/*
** reverse dns resolution for the return packet.
*/
char	*fqdn(t_trace *tr, struct sockaddr_in *addr)
{
	ft_bzero(tr->in.fqdn, sizeof(tr->in.fqdn));
	if (getnameinfo((struct sockaddr *)addr,
			sizeof(struct sockaddr_in), tr->in.fqdn,
			sizeof(tr->in.fqdn), NULL, 0, 0))
		ft_strcpy(tr->in.fqdn, inet_ntoa(addr->sin_addr));
	return (tr->in.fqdn);
}

/*
** gets information on address to be traced (host) and stores
**  into ft_ping->out.daddr
*/
void	get_address(t_trace *tr)
{
	struct addrinfo	hints;
	struct addrinfo	*addr;
	int				ret;

	addr = NULL;
	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_CANONNAME;
	ret = getaddrinfo(tr->argv.hostname, NULL, &hints, &addr);
	if (ret)
	{
		dprintf(STDERR_FILENO, ERR_ADDR, tr->argv.hostname, gai_strerror(ret));
		prs_fatal_pos(tr, ERR_HOST, tr->argv.hostpos);
		if (addr)
			freeaddrinfo(addr);
		exit (1);
	}
	if (addr->ai_canonname)
		ft_strcpy(tr->out.host, addr->ai_canonname);
	tr->out.daddr = *(struct sockaddr_in *)(addr->ai_addr);
	freeaddrinfo(addr);
}
