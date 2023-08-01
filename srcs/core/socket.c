/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:27 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_traceroute.h>

/*
** References:
** https://linux.die.net/man/7/socket
** https://linux.die.net/man/7/ip
** https://linux.die.net/man/2/setsockopt
*/

void	opensocket(t_ping *ft_ping)
{
	int	fd;
	int	vtrue;

	vtrue = 1;
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd < 0)
		prs_fatal(ft_ping, ERR_SOCKET, NULL, false);
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &vtrue, sizeof(vtrue));
	if (ft_ping->opts.ttl && setsockopt(fd, SOL_IP, IP_TTL,
			&(ft_ping->opts.ttl), sizeof(ft_ping->opts.ttl)))
		dprintf(STDERR_FILENO, ERR_SCKOPTTTL, ft_ping->program);
	ft_ping->sock = fd;
}
