/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/18 15:09:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ping_stats(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "--- %s ping statistics ---\n", ft_ping->raw_host);
	dprintf(STDOUT_FILENO,
			"%ld packets transmitted, %ld packets received, ",
			ft_ping->out.count, ft_ping->in.count);
	if (ft_ping->out.count)
		dprintf(STDOUT_FILENO, "%ld%% packet loss",
				 ((ft_ping->out.count - ft_ping->in.count) * 100
				 / ft_ping->out.count));
	dprintf(STDOUT_FILENO, "\n");
}

void ping(t_ping *ft_ping)
{

	t_time	start;
	t_time	timeout = {1,0};

	ft_bzero(&(ft_ping->in), sizeof(ft_ping->in));
	ft_bzero(&(ft_ping->out), sizeof(ft_ping->out));
	ping_out(ft_ping);
	gettimeofday(&start, NULL);
	while (!(g_signal))
	{
		ping_in(ft_ping);
		if (!(g_signal) && timed_out(start, timeout))
		{
			ping_out(ft_ping);
			gettimeofday(&start, NULL);
		}
		usleep(200);
	}
	ping_stats(ft_ping);
}
