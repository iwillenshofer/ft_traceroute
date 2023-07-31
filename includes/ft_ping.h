/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/31 14:40:26 by iwillens         ###   ########.fr       */
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
# include "ft_ping_parse.h"

extern t_bool	g_signal;

void		get_address(t_ping *ft_ping);
void		setup(t_ping *ft_ping, char **argv);
void		ping(t_ping *ft_ping);
void		opensocket(t_ping *ft_ping);

/*
** checksum
*/
t_u16bits	checksum(void *buffer, size_t size);

/*
** time
*/
double		elapsed_time_ms(t_time begin, t_time end);
t_bool		timed_out(t_time begin, t_time timeout);

/*
** ping in/out
*/
t_bool		ping_in(t_ping *ft_ping);
void		ping_out(t_ping *ft_ping, t_bool preload);
void		prebuild_packet(t_ping *ft_ping);
void		build_packet(t_ping *ft_ping);

/*
** duplicate checker
*/
void		set_duptrack(t_ping *ft_ping, size_t seq);
t_bool		check_duptrack(t_ping *ft_ping, size_t seq);
void		clear_duptrack(t_ping *ft_ping, size_t seq);

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
void		print_help(t_ping *ft_ping);
void		print_usage(t_ping *ft_ping);
void		print_shortusage(t_ping *ft_ping);
void		print_version(t_ping *ft_ping);
void		print_headers(t_ping *ft_ping, t_headers *hdr);
void		print_echo(t_ping *ft_ping);

/*
** no echo
*/
void		icmp_noecho(t_ping *ft_ping);
char		*tname(int type);

#endif
