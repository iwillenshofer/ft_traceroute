/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:40:27 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/select.h>
# include <netinet/udp.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include "libft.h"
# include "ft_traceroute_types.h"
# include "ft_traceroute_errors.h"
# include "ft_traceroute_parse.h"

void		setup(t_trace *tr, char **argv);
void		build_packet(t_trace *tr);
void		get_address(t_trace *tr);
void		opensockets(t_trace *tr);
char		*fqdn(t_trace *tr, struct sockaddr_in *addr);
void		set_sockttl(t_trace *tr, size_t ttl);
void		traceroute(t_trace *tr);
void		sendpackets(t_trace *tr);
void		recvpackets(t_trace *tr);
void		prntpackets(t_trace *tr);

/*
** time
*/
double		elapsed_time_ms(t_time begin, t_time end);
t_bool		timed_out(t_time begin, t_time timeout);
t_time		ms_to_time(double ms);
t_time		timetowait(t_trace *tr, t_probe *probe);

/*
** parser
*/
void		parse(t_trace *tr, char **argv);
t_lstopt	*opt_byfullname(t_trace *tr, char *s);
t_lstopt	*opt_byshortcut(t_trace *tr, char c);
void		add_options(t_trace *tr);
void		add_handlers(t_trace *tr);
char		*tname(int type);

/*
** printing
*/
void		print_help(t_trace *tr);
void		print_usage(t_trace *tr, t_bool terminate);
void		print_shortusage(t_trace *tr);
void		print_version(t_trace *tr);
void		print_icmperror(t_icmp *i);
/*
** debugginG
*/
void		print_udp(t_udp *udp);
void		print_icmp(t_icmp *icmp);
void		print_ip(t_ip *ip);
void		color(t_trace *tr, char new_color, char new_opt);

#endif
