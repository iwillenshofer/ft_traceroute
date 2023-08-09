/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 21:24:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** allowed functions:
** getpid / getuid.
** getaddrinfo / gettimeofday.
** inet_ntoa / inet_pton.
** freeaddrinfo
** exit.
** select.
** setsockopt.
** recvfrom / sendto.
** ntohs / htons.
** bind / socket / close.
** strerror / gai_strerror.
** the printf type functions.
** the functions authorized in your libft (read, write, malloc, free).
*/

/*
print header
*/
void	print_init(t_trace *tr)
{
	dprintf(STDOUT_FILENO,
		"traceroute to %s (%s), %lu hops max, %lu byte packets\n",
		tr->out.host, 
		inet_ntoa(tr->out.daddr.sin_addr),
		tr->opts.maxhop, tr->opts.packetsize + sizeof(t_ip) + sizeof(t_udp));
}

int	main(int argc, char **argv)
{
	t_trace	tr;

	setup(&tr, argv);
	opensockets(&tr);
	print_init(&tr);
	traceroute(&tr);
	(void)argc;
	return (0);
}
