/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:16 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:04:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** finishes building the packet and sends a ping.
** if flooding (and not preloading/quiet), prints a '.', which will be erased
** by a receiving message (which will print a backspace.)
*/
void	ping_out(t_ping *ft_ping, t_bool preload)
{
	build_packet(ft_ping);
	if (sendto(ft_ping->sock, ft_ping->out.packet, 
			sizeof(t_icmp) + ft_ping->opts.size, 0,
			(struct sockaddr *)&(ft_ping->out.daddr),
			sizeof(struct sockaddr)) <= 0)
		prs_fatal(ft_ping, ERR_SEND, NULL, false);
	ft_ping->out.count++;
	if ((ft_ping->opts.flood) && !(ft_ping->opts.quiet) && !(preload))
		ft_putchar('.');
}
