/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 00:33:35 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ping_stats(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "--- %s ping statistics ---\n", ft_ping->out.host);
	dprintf(STDOUT_FILENO,
			"%ld packets transmitted, %ld packets received",
			ft_ping->out.count, ft_ping->in.count.total - ft_ping->in.count.dup);
	if (ft_ping->in.count.dup)
		dprintf(STDOUT_FILENO, ", +%ld duplicates", ft_ping->in.count.dup);
	if (ft_ping->in.count.total - ft_ping->in.count.dup > ft_ping->out.count)
		dprintf(STDOUT_FILENO, ", -- somebody is printing forged packets!");
	else if (ft_ping->out.count)
		dprintf(STDOUT_FILENO, ", %ld%% packet loss", ((ft_ping->out.count - (ft_ping->in.count.total - ft_ping->in.count.dup)) * 100 				 / ft_ping->out.count));
	dprintf(STDOUT_FILENO, "\n");
	if (!(ft_ping->in.count.timed))
		return ;
	dprintf(STDOUT_FILENO, "round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
		ft_ping->in.time.min, ft_ping->in.time.avg,
		ft_ping->in.time.max, ft_sqrt(ft_ping->in.time.variance));
}

static t_bool done(t_ping *ft_ping)
{
	if (g_signal)
		return (true);
	if (ft_ping->options.count
			&& ft_ping->options.count <= ft_ping->in.count.total)
		return (true);
	return (false);
}

void	ping_header(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "PING %s (%s): %hu data bytes",
			ft_ping->out.host,
			inet_ntoa(ft_ping->out.daddr.sin_addr),
			ft_ping->options.size);
	if (ft_ping->options.verbose)
	    dprintf(STDOUT_FILENO, ", id 0x%04x = %u", ft_ping->pid, ft_ping->pid);
	dprintf(STDOUT_FILENO, "\n");
}

void ping(t_ping *ft_ping)
{
	t_time	start;
	t_time	timeout = {1,0000};

	ft_bzero(&(ft_ping->in), sizeof(ft_ping->in));
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
