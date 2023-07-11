/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:27 by iwillens          #+#    #+#             */
/*   Updated: 2023/06/27 13:51:19 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

/*
** References:
** https://linux.die.net/man/7/socket
** https://linux.die.net/man/7/ip
** https://linux.die.net/man/2/setsockopt
** 
** SO_RCVTIMEO and SO_SNDTIMEO
** Specify the receiving or sending timeouts until reporting an error.
** The argument is a struct timeval. If an input or output function blocks for
**  this period of time, and data has been sent or received, the return value of
**  that function will be the amount of data transferred; if no data has been
**  transferred and the timeout has been reached then -1 is returned with errno
**  set to EAGAIN or EWOULDBLOCK, or EINPROGRESS (for connect(2)) just as if
** the socket was specified to be nonblocking.
** If the timeout is set to zero (the default) then the operation will never
**  timeout. Timeouts only have effect for system calls that perform socket I/O
** (e.g., read(2), recvmsg(2), send(2), sendmsg(2));
**  timeouts have no effect for select(2), poll(2), epoll_wait(2), and so on.
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

int	opensocket(void)
{	
	get_options();
	int ttl_val = 62;
    struct timeval tv_out;
    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;
	int fd;
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	printf("socket: %d\n", fd);
	if (setsockopt(fd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)))
		printf("error setting sock option 1.\n");
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(struct timeval)))
		printf("error setting sock option 2.\n");
	return (fd);
}
