/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/19 13:27:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ping_stats(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "--- %s ping statistics ---\n", ft_ping->raw_host);
	dprintf(STDOUT_FILENO,
			"%ld packets transmitted, %ld packets received, ",
			ft_ping->out.count, ft_ping->in.replies);
	if (ft_ping->out.count)
		dprintf(STDOUT_FILENO, "%ld%% packet loss",
				 ((ft_ping->out.count - ft_ping->in.count) * 100
				 / ft_ping->out.count));
	dprintf(STDOUT_FILENO, "\n");
	if (!(ft_ping->in.time.record))
		return ;
	dprintf(STDOUT_FILENO, "round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
		ft_ping->in.time.min, ft_ping->in.time.avg,
		ft_ping->in.time.max, ft_sqrt(ft_ping->in.time.variance));
}

static t_bool done(t_ping *ft_ping)
{
	if (g_signal)
		return (true);
	if (ft_ping->options.all.count
			&& ft_ping->options.all.count <= ft_ping->in.count)
		return (true);
	return (false);
}

void	ping_header(t_ping *ft_ping)
{
	/* WILL FIX THAT AND PUT IN OUR FT_PING STRUCT A.S.A.P.*/
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &((struct sockaddr_in *)ft_ping->addr_send->ai_addr)->sin_addr, str, INET_ADDRSTRLEN);

	dprintf(STDOUT_FILENO, "PING %s (%s): %hu data bytes\n",
			ft_ping->raw_host,
			str,
			ft_ping->options.echo.size);
}

void ping(t_ping *ft_ping)
{
	t_time	start;
	t_time	timeout = {1,0};

	ft_bzero(&(ft_ping->in), sizeof(ft_ping->in));
	ft_bzero(&(ft_ping->out), sizeof(ft_ping->out));
	ping_header(ft_ping);
	ping_out(ft_ping);
	gettimeofday(&start, NULL);
	while (!(done(ft_ping)))
	{
		ping_in(ft_ping);
		if (!(done(ft_ping)) && timed_out(start, timeout))
		{
			ping_out(ft_ping);
			gettimeofday(&start, NULL);
		}
		usleep(200);
	}
	ping_stats(ft_ping);
}
