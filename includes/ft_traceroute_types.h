/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:15 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/31 15:00:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_TYPES_H
# define FT_TRACEROUTE_TYPES_H

# include "ft_traceroute_parse.h"


# define DFL_PACKETSIZE			32 /* plus 20iphdr, 8udphdr = 60 */
# define DFL_MAXTTL				30
# define DFL_FIRSTTTL			1
# define DFL_STARTPORT			33434
# define DFL_NQUERIES			3
# define DFL_SQUERIES			16
# define MAX_PROBESPERHOP		10
# define MAX_HOPS				255
# define MAX_PACKET				65000
# define MAX_SQUERIES			DFL_MAXHOPS * MAX_PROBESPERHOP
# define MAX_PORT				65536

/*
** So, let's start building our traceroute structure, starting from here.
** What we need is a main structure, which will have main information about our
** client (local address? port used? counters? packet?)
** Then we will have a structure for each of the hops (default is 30 hops...)
**  and inside of it, we will have an structure for each of the probs
**  (default is 3 probes...)
*/

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct timeval	t_time;
typedef struct iphdr	t_ip;
typedef struct udphdr	t_udp;
typedef struct udphdr	t_icmp;
typedef struct in_addr	t_inaddr;
struct s_trace; /* forward declaration for traceroute */


typedef struct s_lstopt
{
	char	shortcut;
	int		type;
	char	fullname[24];
	char	desc[128];
	void	(*handler)(struct s_trace *, struct s_lstopt *opt, char *val);
}	t_lstopt;


typedef struct s_options
{
	t_bool		resolvehosts;
	size_t		firsthop;
	size_t		maxhop;	
	size_t		port;
	size_t		squeries;
	size_t		nqueries;
	size_t		packetsize;
	t_lstopt	available[OPT_LSTSIZE];
}	t_options;

typedef struct s_probe
{
	t_bool				sent;
	t_bool				received;
	int					sock;
	in_port_t			port;
	t_time				ts;
	t_time				tr;
	struct sockaddr_in	daddr;
	struct sockaddr_in	bindaddr;
}	t_probe;

typedef struct s_hop
{
	size_t	id;
	t_probe	probe[MAX_PROBESPERHOP];
}	t_hop;

typedef struct s_outloop
{
	int					sock;
	char				host[NI_MAXHOST + 1];
	char				fqdn[NI_MAXHOST + 1];
	char				packet[MAX_PACKET];
	struct sockaddr_in	daddr;
}	t_outloop;

typedef struct s_counter
{
	size_t		recv;
	size_t		sent;
}	t_counter;

typedef struct s_inloop
{
	int		sock;
	char	buf[MAX_PACKET];
}	t_inloop;


typedef struct s_trace
{
	t_outloop	out;
	t_inloop	in;
	t_counter	count;
	t_hop		hop[MAX_HOPS];
	t_options	opts;
	fd_set		readfds;
	fd_set		errfds;
	char		*program;
	char		*hostname;
}	t_trace;

/*
** --------
*/

# define ERROR_BUFFER_SIZE 			64
# define DFL_PACKET_SIZE 			56
# define DFL_CUSTOM_PATTERN_SIZE 	16
# define DFL_TTL					64
# define DFL_USLEEP					200
# define MAX_PACKET_SIZE			65399
# define PACKET_BUFFER_SIZE			65535
# define MAX_SEQ_TRACK				128
# define MAX_PATTERN				31
# define NI_MAXHOST     			1025
# define MIN_ICMP_RATE				5000
# define DFL_FLOOD_RATE				10000

#endif
