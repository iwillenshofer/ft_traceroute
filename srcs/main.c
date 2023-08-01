/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

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

t_bool	g_signal = false;

void	shandler(int signal)
{
	if (signal == SIGINT)
		g_signal = true;
}

int	main(int argc, char **argv)
{
	t_ping	ft_ping;

	setup(&ft_ping, argv);
	signal(SIGINT, shandler);
	opensocket(&ft_ping);
	gettimeofday(&(ft_ping.begin), NULL);
	while (*(++argv))
	{
		ft_bzero(&(ft_ping.out), sizeof(ft_ping.out));
		ft_strcpy(ft_ping.out.host, *argv);
		get_address(&ft_ping);
		ping(&ft_ping);
	}
	close(ft_ping.sock);
	(void)argc;
	return (0);
}
