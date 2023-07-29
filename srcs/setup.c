/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:42:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:06:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file sets up the ft_ping structure.
*/

#include "ft_ping.h"

static void	set_defaults(t_ping *ft_ping)
{
	ft_ping->opts.size = DFL_PACKET_SIZE;
	ft_ping->opts.interval.tv_sec = 1;
}

/*
** after parsing, set the options
*/
static void	set_options(t_ping *ft_ping)
{
	if (ft_ping->opts.flood || (!(ft_ping->opts.interval.tv_sec)
			&& ft_ping->opts.interval.tv_usec < 10000))
	{
		ft_ping->opts.interval.tv_sec = 0;
		ft_ping->opts.interval.tv_usec = 10000;
	}
}

void	setup(t_ping *ft_ping, char **argv)
{
	ft_bzero(ft_ping, sizeof(t_ping));
	add_options(ft_ping);
	set_defaults(ft_ping);
	parse(ft_ping, argv);
	set_options(ft_ping);
	ft_ping->pid = (unsigned short)getpid(); 
}
