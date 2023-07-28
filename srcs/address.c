/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:52:05 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 18:24:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
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

static char *inetname(t_inaddr *in)
{
	static char line[50];
	struct hostent *hostentity;

	hostentity = gethostbyaddr((char *)in, sizeof (*in), AF_INET);
	if (hostentity && hostentity->h_name) {
		(void) strcpy(line,  hostentity->h_name); 
	}
	return (line);
}

/*
** gets information on address to be ping'ed (host) and stores
**  into ft_ping->addr_send, to be used by ping().
*/
void	get_address(t_ping *ft_ping)
{
	struct addrinfo hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_flags = AI_CANONNAME;
	if(getaddrinfo(ft_ping->raw_host, NULL, &hints, &(ft_ping->addr_send)))
		prs_fatal(ft_ping, ERR_UNKNOWN_HOST, NULL, false);
	if (ft_ping->addr_send->ai_canonname)
		ft_strcpy(ft_ping->raw_host, ft_ping->addr_send->ai_canonname);
}

char *qualified_address(t_ping *ft_ping, t_inaddr *in)
{
	char *ret;

	ret = inetname(in);
	if (!ret || !(*ret))
		ret = ft_ping->raw_host;
	ft_bzero(ft_ping->qualified_address, sizeof(ft_ping->qualified_address));
	sprintf(ft_ping->qualified_address, "(%s) %s", ret, inet_ntoa(*in));
	return (ft_ping->qualified_address);
}
