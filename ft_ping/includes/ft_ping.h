/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:32:46 by iwillens         ###   ########.fr       */
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
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_ping_types.h"
# include "ft_ping_errors.h"
# include "ft_ping_endianess.h"

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

int		opensocket(void);
void	get_address(t_ping *ft_ping);
void	print_addrinfo(struct addrinfo *head);
void	print_icmpheader(t_icmpheader *head);

void	print_ipheader(t_ipheader *head);
void	setup(t_ping *ft_ping, char **argv);
void	print_usage(t_ping *ft_ping);
char	*qualified_address(t_ping *ft_ping, struct in_addr *in);
void	ping(t_ping *ft_ping);
void	fatal(t_ping *ft_ping,char *msg, t_bool usage);

#endif
