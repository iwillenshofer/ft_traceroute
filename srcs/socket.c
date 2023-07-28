/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:27 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 18:34:43 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

/*
** References:
** https://linux.die.net/man/7/socket
** https://linux.die.net/man/7/ip
** https://linux.die.net/man/2/setsockopt
*/

/*
** function to test socket
*/
void get_options(void)
{
	int ttl_val = 0;
	socklen_t optlen;
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (getsockopt(sock, SOL_IP, IP_TTL, &ttl_val, &optlen))
		printf("ERROR GETTING SOCKOPT\n");
	printf("current TTL:%i\n", ttl_val);
	close(sock);
}

void	opensocket(t_ping *ft_ping)
{	
    t_time tv_out;
	int fd;
    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0; (void)tv_out;
	int allow_broadcast;

	allow_broadcast = 1;
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (setsockopt(fd, SOL_IP, IP_TTL, &(ft_ping->options.ttl), sizeof(ft_ping->options.ttl)))
		printf("error setting sock option 1.\n");
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &allow_broadcast, sizeof(allow_broadcast)))
		printf("error setting sock option 1.\n");
//    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(t_time)))
//		printf("error setting sock option 2.\n");
	ft_ping->sock = fd;
}
