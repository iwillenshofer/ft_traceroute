/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/04 18:57:35 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
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
** So, in our main, we will just parse the arguments and set the default options.
** options to be implemented for bonus:
** f --first-hop (1-255)
** m --max-hop (1-255)
** p --port (1-65536, but if too high, sendto will throw an error)
** w --wait (0 - 60)
** q --tries (1 - 10)
** ? --help
** m --resolve-names
** u --usage
** V --version
*/
int	main(int argc, char **argv)
{
	t_trace	tr;

	setup(&tr, argv);
	opensockets(&tr);
	while (1)
		trace(&tr);

//	opensocket(&ft_ping);
//	gettimeofday(&(ft_ping.begin), NULL);
//	while (*(++argv))
//	{
//		ft_bzero(&(ft_ping.out), sizeof(ft_ping.out));
//		ft_strcpy(ft_ping.out.host, *argv);
//		get_address(&ft_ping);
//		ping(&ft_ping);
//	}
//	close(ft_ping.sock);
	(void)argc;
	return (0);
}
