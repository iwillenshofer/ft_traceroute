/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_types.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:15 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 22:42:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_TYPES_H
# define FT_TRACEROUTE_TYPES_H

# include "ft_traceroute_parse.h"

# define DFL_PACKETSIZE			32
# define DFL_MAXTTL				30
# define DFL_FIRSTTTL			1
# define DFL_STARTPORT			33434
# define DFL_NQUERIES			3
# define DFL_SQUERIES			16
# define DFL_SLEEP				100
# define DFL_TIMEOUTMS			5000
# define MAX_PROBESPERHOP		10
# define MAX_HOPS				255
# define MAX_PACKET				65000
# define MAX_SQUERIES			2550
# define MAX_PORT				65536

/*
** definitions for colors
*/

# define BLACK 30
# define RED 31
# define GREEN 32
# define YELLOW 33
# define BLUE 34
# define PURPLE 35
# define CYAN 36
# define WHITE 37
# define RESET 0

# define REGULAR 0
# define BOLD 1
# define FAINT 2

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
typedef struct icmphdr	t_icmp;
typedef struct in_addr	t_inaddr;

typedef struct s_trace	t_trace;

typedef struct s_lstopt
{
	char	shortcut;
	int		type;
	char	fullname[24];
	char	desc[128];
	void	(*handler)(t_trace *, struct s_lstopt *opt, char *val);
}	t_lstopt;

typedef struct s_headers
{
	t_bool	valid;
	t_ip	ip;
	t_icmp	icmp;
	t_ip	oip;
	t_udp	oudp;
}	t_headers;

typedef struct s_options
{
	t_bool		nodns;
	t_bool		color;
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
	size_t				id;
	size_t				idx;
	size_t				hdx;
	t_time				ts;
	t_time				tr;
	t_bool				sent;
	in_port_t			port;
	t_bool				received;
	t_bool				timedout;
	t_headers			headers;
	double				elapsed;
	struct sockaddr_in	daddr;
	struct sockaddr_in	saddr;
}	t_probe;

typedef struct s_hop
{
	size_t	id;
	size_t	ttl;
	t_bool	lasthop;
	t_probe	probe[MAX_PROBESPERHOP];
}	t_hop;

typedef struct s_outloop
{
	int					sock;
	char				host[NI_MAXHOST + 1];
	char				packet[MAX_PACKET];
	struct sockaddr_in	daddr;
}	t_outloop;

/*
** counter for received, sent and printed
*/
typedef struct s_counter
{
	size_t		recv;
	size_t		timedout;
	size_t		sent;
	size_t		prt;
}	t_counter;

typedef struct s_inloop
{
	int					sock;
	struct sockaddr_in	saddr;
	socklen_t			saddrlen;
	fd_set				rfds;
	char				buf[MAX_PACKET];
	char				fqdn[NI_MAXHOST + 1];
}	t_inloop;

/*
** saves information about argv for parsing
*/
typedef struct s_argv
{
	char	**argv;
	char	*program;
	char	*hostname;
	char	**hostpos;
}	t_argv;

typedef struct s_trace
{
	t_bool		done;
	t_outloop	out;
	t_inloop	in;
	t_counter	count;
	t_hop		hop[MAX_HOPS];
	t_options	opts;
	t_argv		argv;
}	t_trace;

#endif
