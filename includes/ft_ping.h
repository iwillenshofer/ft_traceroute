/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 12:26:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <signal.h>
# include "libft.h"
# include "ft_ping_types.h"
# include "ft_ping_errors.h"

# ifdef BONUS
#  define IS_BONUS 1
#  include "ft_ping_bonus.h"
# else
#  define IS_BONUS 0
# endif

# ifndef OPTS_SINGLE
#  define OPTS_SINGLE "hv"
# endif

# ifndef OPTS_DOUBLE
#  define OPTS_DOUBLE ""
# endif

# define FALSE 0
# define TRUE 1

extern t_bool g_signal;


void	opensocket(t_ping *ft_ping);
void	get_address(t_ping *ft_ping);
void	print_addrinfo(struct addrinfo *head);
void	print_icmpheader(t_icmpheader *head);

void	print_ipheader(t_ipheader *head);
void	setup(t_ping *ft_ping, char **argv);
void	print_usage(t_ping *ft_ping);
char	*qualified_address(t_ping *ft_ping, struct in_addr *in);
void	ping(t_ping *ft_ping);
void	fatal(t_ping *ft_ping,char *msg, t_bool usage);


/*
** Endianess
*/
t_u16bits	bytes16_le(t_u16bits hostshort);
t_u32bits	bytes32_le(t_u32bits hostlong);
t_u8bits	bitfield8_le(t_u8bits hostshort);

/*
** checksum
*/
t_u16bits	checksum(void *buffer, size_t size);

/*
** time
*/
t_time elapsed_time(t_time begin, t_time end);
ssize_t elapsed_time_ms(t_time begin, t_time end);
t_bool timed_out(t_time begin, t_time timeout);

/*
** ping in/out
*/
t_bool	ping_in(t_ping *ft_ping);
void	ping_out(t_ping *ft_ping);

/*
** duplicate checker
*/
t_bool	check_duptrack(t_ping *ft_ping, size_t seq);
void	set_duptrack(t_ping *ft_ping, size_t seq);

/*
** parser
*/
void	parse(t_ping *ft_ping, char **argv);

#endif
