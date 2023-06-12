/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/06/12 16:08:53 by iwillens         ###   ########.fr       */
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
** PING USES ICMP: RFC 792
** https://datatracker.ietf.org/doc/html/rfc792
*/

#include <stdio.h>

int	main(void)
{	
	int	fd;

	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	printf("protocol: %d\n", fd);
	return (0);
}
