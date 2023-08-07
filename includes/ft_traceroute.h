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
# include "libft.h"
# include <netinet/udp.h>
# include <netinet/ip_icmp.h>

# include <netinet/ip.h>
# include <linux/if_ether.h>

# include "ft_traceroute_types.h"
# include "ft_traceroute_errors.h"
# include "ft_traceroute_parse.h"

void		trace(t_trace *tr);
void		setup(t_trace *tr, char **argv);
void		build_packet(t_trace *tr);

void		get_address(t_trace *tr);
void		opensockets(t_trace *tr);
void		set_sockttl(t_trace *tr, size_t ttl);

void		ping(t_trace *tr);
/*
** time
*/
double		elapsed_time_ms(t_time begin, t_time end);
t_bool		timed_out(t_time begin, t_time timeout);

/*
** ping in/out
*/
t_bool		ping_in(t_trace *tr);
void		ping_out(t_trace *tr, t_bool preload);
void		prebuild_packet(t_trace *tr);

/*
** duplicate checker
*/
void		set_duptrack(t_trace *tr, size_t seq);
t_bool		check_duptrack(t_trace *tr, size_t seq);
void		clear_duptrack(t_trace *tr, size_t seq);

/*
** parser
*/
void		parse(t_trace *tr, char **argv);
t_lstopt	*opt_byfullname(t_trace *tr, char *s);
t_lstopt	*opt_byshortcut(t_trace *tr, char c);
void		add_options(t_trace *tr);
void		add_handlers(t_trace *tr);

/*
** printing
*/
void		print_help(t_trace *tr);
void		print_usage(t_trace *tr);
void		print_shortusage(t_trace *tr);
void		print_version(t_trace *tr);
void		print_echo(t_trace *tr);

/*
** no echo
*/
void		icmp_noecho(t_trace *tr);
char		*tname(int type);

void		traceroute(t_trace *tr);
#endif
