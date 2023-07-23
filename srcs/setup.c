/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:42:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 22:16:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file sets up the ft_ping structure.
*/

#include "ft_ping.h"

void	set_defaults(t_ping *ft_ping)
{
	ft_ping->options.echo.size = DFL_PACKET_SIZE;
	ft_ping->options.all.ttl = DFL_TTL;
}

void	setup(t_ping *ft_ping, char **argv)
{
	ft_bzero(ft_ping, sizeof(t_ping));
	set_defaults(ft_ping);
	parse(ft_ping, argv);
	ft_ping->pid = getpid();
}
