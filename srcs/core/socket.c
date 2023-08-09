/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:27 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 00:55:58 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_traceroute.h>

/*
** References:
** https://linux.die.net/man/7/socket
** https://linux.die.net/man/7/ip
** https://linux.die.net/man/2/setsockopt
*/

#define ERR_BIND "ERR_BIND\n"
#define ERR_SOCKET "ERR_SOCKET\n"

/*
** binds the UDP socket to any addr.
*/
static void	bindsocket(t_trace *tr)
{
	struct sockaddr_in saddr;

	ft_bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(0);
	bind(tr->out.sock, (struct sockaddr*)&(saddr), sizeof(saddr));
}

/*
** sets socket options for the outgoing socket
*/
static void	socketoptions(t_trace *tr)
{
	int t;

	t = 1;
	if (setsockopt(tr->in.sock, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t)) < 0)
		prs_fatal(tr, "SO_REUSEPORT\n", NULL, false);
	if (setsockopt(tr->out.sock, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t)) < 0)
		prs_fatal(tr, "SO_REUSEPORT\n", NULL, false);
}

/*
** sets the TTL for the current HOP
*/
void	set_sockttl(t_trace *tr, size_t ttl)
{
	if (setsockopt (tr->out.sock, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		prs_fatal(tr, "IP_TTL\n", NULL, false);
}

void	opensockets(t_trace *tr)
{
	int	fd;

	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd < 0)
		prs_fatal(tr, ERR_SOCKET, NULL, false);
	tr->in.sock = fd;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		prs_fatal(tr, ERR_SOCKET, NULL, false);
	tr->out.sock = fd;
	bindsocket(tr);
	socketoptions(tr);
}
