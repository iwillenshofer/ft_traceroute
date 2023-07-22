/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/22 13:16:57 by iwillens         ###   ########.fr       */
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

t_bool g_signal = false;

void	shandler(int signal)
{
	if (signal == SIGINT)
		g_signal = true;
}

void	leave_graciously(t_ping *ft_ping)
{
	if (ft_ping->packet)
		free(ft_ping->packet);
}

int	main(int argc, char **argv)
{
	t_ping ft_ping;
	
	setup(&ft_ping, argv);
	signal(SIGINT, shandler);
	opensocket(&ft_ping);
	while (*(++argv))
	{
		ft_strcpy(ft_ping.raw_host, *argv);
		get_address(&ft_ping);
		ping(&ft_ping);
		freeaddrinfo((ft_ping.addr_send));
	}
	close(ft_ping.sock);
	leave_graciously(&ft_ping);
	(void)argc;
	return (0);
}
