/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 11:03:38 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** allowed functions:
** gettimeofday.
** exit.
** inet_ntop. / inet_pton.
** signal / alarm.
** socket / setsockopt.
** sendto / recvmsg.
** getpid / getuid.
** getaddrinfo / freeaddrinfo.
** strerror / gai_strerror.
** printf and its family.
*/

/*
** socket
** int socket(int domain, int type, int protocol);
*/

/*
PING USES ICMP: RFC 792
https://datatracker.ietf.org/doc/html/rfc792
*/

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_ping ft_ping;
	setup(&ft_ping, argv);
	
	get_address(&ft_ping);
	ft_ping.sock = opensocket();
	ping(&ft_ping);
	close(ft_ping.sock);
	freeaddrinfo((ft_ping.addr_send));
	(void)argc;
	return (0);
}
