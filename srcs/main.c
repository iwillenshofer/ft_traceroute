/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 15:50:46 by iwillens         ###   ########.fr       */
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
	color(tr, PURPLE, BOLD);
	dprintf(STDOUT_FILENO, "traceroute to");
	color(tr, WHITE, BOLD);
	dprintf(STDOUT_FILENO, " %s ", tr->out.host);
	color(tr, WHITE, FAINT);
	dprintf(STDOUT_FILENO, "(%s),", inet_ntoa(tr->out.daddr.sin_addr));
	color(tr, PURPLE, BOLD);
	dprintf(STDOUT_FILENO, " %lu", tr->opts.maxhop);
	color(tr, PURPLE, FAINT);
	dprintf(STDOUT_FILENO, " hops max, ");
	color(tr, PURPLE, BOLD);
	dprintf(STDOUT_FILENO, "%lu", tr->opts.packetsize + sizeof(t_ip) + sizeof(t_udp));
	color(tr, PURPLE, FAINT);
	dprintf(STDOUT_FILENO, " byte packets\n");
	color(tr, RESET, REGULAR);
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
