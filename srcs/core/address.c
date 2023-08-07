/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:52:05 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/04 22:19:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <limits.h>

/*
**	struct addrinfo {
**		int              ai_flags;
**		int              ai_family;
**		int              ai_socktype;
**		int              ai_protocol;
**		socklen_t        ai_addrlen;
**		struct sockaddr *ai_addr;
**		char            *ai_canonname;
**		struct addrinfo *ai_next;
**	};
**
**	struct sockaddr {
**		unsigned short    sa_family;    // address family, AF_xxx
**		char              sa_data[14];  // 14 bytes of protocol address
**	}; 
**
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
**
**	int getaddrinfo(const char *node, const char *service,
**						const struct addrinfo *hints,
**						struct addrinfo **res);
*/

static void	get_fqdn(t_trace *tr)
{
	ft_bzero(tr->out.fqdn, sizeof(tr->out.fqdn));
	if (getnameinfo((struct sockaddr *)&(tr->out.daddr),
			sizeof(tr->out.daddr), tr->out.fqdn,
			sizeof(tr->out.fqdn), NULL, 0, 0))
		ft_strcpy(tr->out.fqdn, inet_ntoa(tr->out.daddr.sin_addr));
}

/*
** gets information on address to be ping'ed (host) and stores
**  into ft_ping->out.daddr, to be used by ping().
*/
void	get_address(t_trace *tr)
{
	struct addrinfo	hints;
	struct addrinfo	*addr;
	int				ret;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_CANONNAME;
	ret = getaddrinfo(tr->hostname, NULL, &hints, &addr);
	if (ret)
		prs_fatal(tr, ERR_UNKNOWN_HOST, NULL, false);
	if (addr->ai_canonname)
		ft_strcpy(tr->out.host, addr->ai_canonname);
	tr->out.daddr = *(struct sockaddr_in *)(addr->ai_addr);
	freeaddrinfo(addr);
	get_fqdn(tr);
}
