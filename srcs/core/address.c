/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:52:05 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
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

static void	get_fqdn(t_ping *ft_ping)
{
	ft_bzero(ft_ping->out.fqdn, sizeof(ft_ping->out.fqdn));
	if (getnameinfo((struct sockaddr *)&(ft_ping->out.daddr),
			sizeof(ft_ping->out.daddr), ft_ping->out.fqdn,
			sizeof(ft_ping->out.fqdn), NULL, 0, 0))
		ft_strcpy(ft_ping->out.fqdn, inet_ntoa(ft_ping->out.daddr.sin_addr));
}

/*
** gets information on address to be ping'ed (host) and stores
**  into ft_ping->out.daddr, to be used by ping().
*/
void	get_address(t_ping *ft_ping)
{
	struct addrinfo	hints;
	struct addrinfo	*addr;
	int				ret;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = AI_CANONNAME;
	ret = getaddrinfo(ft_ping->out.host, NULL, &hints, &addr);
	if (ret)
		prs_fatal(ft_ping, ERR_UNKNOWN_HOST, NULL, false);
	if (addr->ai_canonname)
		ft_strcpy(ft_ping->out.host, addr->ai_canonname);
	ft_ping->out.daddr = *(struct sockaddr_in *)(addr->ai_addr);
	freeaddrinfo(addr);
	get_fqdn(ft_ping);
}
