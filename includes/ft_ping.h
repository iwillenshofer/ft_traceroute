/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 18:09:04 by iwillens         ###   ########.fr       */
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
#  define OPTS_SINGLE "vUnfq?V"
# endif

# ifndef OPTS_DOUBLE
#  define OPTS_DOUBLE "Twcislp"
# endif


/*
** ICMP TYPES not included in header (for error response handling)
*/
# define ICMP_CSRTR_ADV 9 
# define ICMP_CSRTR_DSC 10

# define FALSE 0
# define TRUE 1

extern t_bool g_signal;


void	opensocket(t_ping *ft_ping);
void	get_address(t_ping *ft_ping);
void	print_addrinfo(struct addrinfo *head);
void	print_icmp(t_icmp *head);


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
double elapsed_time_ms(t_time begin, t_time end);
t_bool timed_out(t_time begin, t_time timeout);

/*
** ping in/out
*/
t_bool	ping_in(t_ping *ft_ping);
void	ping_out(t_ping *ft_ping);

/*
** duplicate checker
*/
void	set_duptrack(t_ping *ft_ping, size_t seq);
t_bool	check_duptrack(t_ping *ft_ping, size_t seq);
void	clear_duptrack(t_ping *ft_ping, size_t seq);

/*
** parser
*/
void		parse(t_ping *ft_ping, char **argv);
t_lstopt	*opt_byfullname(t_ping *ft_ping, char *s);
t_lstopt	*opt_byshortcut(t_ping *ft_ping, char c);
void		add_options(t_ping *ft_ping);
void		add_handlers(t_ping *ft_ping);

/*
** printing
*/
void	print_help(t_ping *ft_ping);
void	print_usage(t_ping *ft_ping);
void	print_shortusage(t_ping *ft_ping);
void	print_version(t_ping *ft_ping);
void	print_headers(t_ping *ft_ping, t_headers *hdr);
void	print_echo(t_ping *ft_ping);

/*
** no echo
*/
void	icmp_noecho(t_ping *ft_ping);

#endif
