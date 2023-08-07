/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:42:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/07 18:36:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** after parsing, set the defaultoptions.
** if packetsize has been set, we have to subtract the headers from it.
*/
static void	set_defaults(t_trace *tr)
{
	if (!(tr->opts.packetsize))
		tr->opts.packetsize = DFL_PACKETSIZE;
	else if (tr->opts.packetsize <= (sizeof(t_ip) + sizeof(t_udp)))
		tr->opts.packetsize = 0;
	else
		tr->opts.packetsize = tr->opts.packetsize
			- (sizeof(t_ip) + sizeof(t_udp));
	if (!(tr->opts.port))
		tr->opts.port = DFL_STARTPORT;
	if (!(tr->opts.squeries))
		tr->opts.squeries = DFL_SQUERIES;
	if (!(tr->opts.nqueries))
		tr->opts.nqueries = DFL_NQUERIES;
	if (!(tr->opts.maxhop))
		tr->opts.maxhop = DFL_MAXTTL;
	tr->opts.timeout.tv_sec = 3;
}

void	setup(t_trace *tr, char **argv)
{
	ft_bzero(tr, sizeof(t_trace));
	add_options(tr);
	parse(tr, argv);
	set_defaults(tr);
	build_packet(tr);
	get_address(tr);
}
