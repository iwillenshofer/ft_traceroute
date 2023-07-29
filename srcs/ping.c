/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:05:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ping_stats(t_ping *ft_ping)
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
		dprintf(STDOUT_FILENO, ", %ld%% packet loss",
			((ft_ping->out.count
					- (ft_ping->in.count.total - ft_ping->in.count.dup)) * 100
				/ ft_ping->out.count));
	dprintf(STDOUT_FILENO, "\n");
	if (!(ft_ping->in.count.timed))
		return ;
	dprintf(STDOUT_FILENO,
		"round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
		ft_ping->in.time.min, ft_ping->in.time.avg,
		ft_ping->in.time.max, ft_sqrt(ft_ping->in.time.variance));
}

/*
** checks if we are done pinging (at all) or just sending
** if sending == true;
*/
static t_bool	done(t_ping *ft_ping, t_bool sending)
{
	if (g_signal)
		return (true);
	if (ft_ping->opts.count
		&& ft_ping->opts.count <= ft_ping->in.count.total)
		return (true);
	if (sending && ft_ping->opts.count
		&& ft_ping->opts.count <= ft_ping->out.count)
		return (true);
	if (ft_ping->opts.timeout.tv_sec
		&& timed_out(ft_ping->begin, ft_ping->opts.timeout))
		return (true);
	return (false);
}

void	ping_header(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "PING %s (%s): %hu data bytes",
		ft_ping->out.host,
		inet_ntoa(ft_ping->out.daddr.sin_addr),
		ft_ping->opts.size);
	if (ft_ping->opts.verbose)
		dprintf(STDOUT_FILENO, ", id 0x%04x = %u", ft_ping->pid, ft_ping->pid);
	dprintf(STDOUT_FILENO, "\n");
}

void	preload(t_ping *ft_ping)
{
	size_t	i;

	i = 0;
	if (!(ft_ping->opts.preload))
		return ;
	while (++i <= ft_ping->opts.preload)
		ping_out(ft_ping, true);
}

void	ping(t_ping *ft_ping)
{
	t_time	start;

	ft_bzero(&(ft_ping->in), sizeof(ft_ping->in));
	prebuild_packet(ft_ping);
	ping_header(ft_ping);
	preload(ft_ping);
	ping_out(ft_ping, false);
	gettimeofday(&start, NULL);
	while (!(done(ft_ping, false)))
	{
		ping_in(ft_ping);
		if (!(done(ft_ping, true)) && timed_out(start, ft_ping->opts.interval))
		{
			ping_out(ft_ping, false);
			gettimeofday(&start, NULL);
		}
		usleep(DFL_USLEEP);
	}
	ping_stats(ft_ping);
}
