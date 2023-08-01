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
# define OPT_COUNT					0
# define OPT_INTERVAL				1
# define OPT_NUMERIC				2
# define OPT_TTL					3
# define OPT_VERBOSE				4
# define OPT_TIMEOUT				5
# define OPT_FLOOD					6
# define OPT_PRELOAD				7
# define OPT_PATTERN				8
# define OPT_QUIET					9
# define OPT_SIZE					10
# define OPT_HELP					11
# define OPT_USAGE					12
# define OPT_VERSION				13
# define OPT_OPTIONS_SIZE			14
# define OPTT_NULL					0
# define OPTT_SHORT					1
# define OPTT_LONG					2
# define OPTT_PATTERN				3

/*
** ICMP TYPES not included in header (for error response handling)
*/
# define ICMP_CSRTR_ADV 9 
# define ICMP_CSRTR_DSC 10

typedef enum e_bool
{
	false,
	true
}	t_bool;

/*
** forward declaration of s_ping for use in options.
*/
struct					s_ping;

typedef struct timeval	t_time;

/*
** define unsigned 8, 16 and 32 bits variables. Those are
** system defined as __be16, __be32... but I'm defining it myself
** for learning purposes, testing and reference.
** for 32bits systems, 32bits should be unsigned long instead of
** int, but I didn't implement it as I found unecessary for this project.
*/
typedef unsigned char	t_u8bits;
typedef unsigned short	t_u16bits;
typedef unsigned int	t_u32bits;

/*
** the Internet protocol and the icmp protocol headers.
** Although these structures are defined on the headers <netinet/ip_icmp.h> and
** and <netinet/ip.h>, I have recoded them (using simplified types, reducing
** abstractions and internal system's typedefs), following the ip and icmp RFCs
** for learning purposes.
** RFC for Internet Protocol:
**  https://datatracker.ietf.org/doc/html/rfc791
** RFC for Internet Control Message Protocol:
**  https://datatracker.ietf.org/doc/html/rfc792
** 
**  A summary of the contents of the internet header follows:
**   0                   1                   2                   3
**   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |Version|  IHL  |Type of Service|          Total Length         |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |         Identification        |Flags|      Fragment Offset    |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |  Time to Live |    Protocol   |         Header Checksum       |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |                       Source Address                          |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |                    Destination Address                        |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**  |                    Options                    |    Padding    |
**  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**	Source: RFC 791
**
** These variables are defined in the iphdr structure, typedef'd
** below.
*/

typedef struct iphdr	t_ip;

/*
** Echo or Echo Reply Message
**
**    0                   1                   2                   3
**    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
**   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**   |     Type      |     Code      |          Checksum             |
**   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**   |           Identifier          |        Sequence Number        |
**   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
**   |     Data ...
**   +-+-+-+-+-
**
** PING USES ICMP: RFC 792
*/

typedef struct icmphdr	t_icmp;

/*
** simple struct to parse buffer into, and make it easier to access
** ip and icmp headers, as well as data, without having to do multiple
** casting
*/

typedef struct in_addr	t_inaddr;

typedef struct s_headers
{
	t_ip		*ip;
	t_icmp		*icmp;
	char		*data;
	size_t		datalen;
}	t_headers;

/*
** message structure defined in socket.h to pass as argument to
** recvmsg(), and contains pointers to buffer and address structures
** as well as information about said buf/struct sizes.
** system's implementation is:
**struct msghdr {
**  void *msg_name;			: address of a sockaddr struct
**  socklen_t msg_namelen;	: its len
**  struct iovec *msg_iov;	: pointer to iovec [data* / datalen]
**  size_t msg_iovlen;		: iovec struct len
**  ... };					: other fields are unused in our implementation.
*/

typedef struct msghdr	t_msghdr;

/*
** options for all kinds of requests
*/

typedef struct s_options_pattern
{
	t_u8bits	pattern[DFL_CUSTOM_PATTERN_SIZE];
	t_u8bits	size;
}	t_options_pattern;

typedef struct s_lstopt
{
	char	shortcut;
	int		type;
	char	fullname[16];
	char	desc[128];
	void	(*handler)(struct s_ping *, struct s_lstopt *opt, char *val);
}	t_lstopt;

typedef struct s_options
{
	t_bool				flood;
	t_bool				quiet;
	t_bool				numeric;
	t_bool				verbose;
	t_bool				int_set;
	t_u32bits			preload;
	t_options_pattern	pattern;
	t_u32bits			size;	
	t_u32bits			count;
	t_time				interval;
	t_u8bits			ttl;
	t_time				timeout;
	t_lstopt			available[OPT_LSTSIZE];
}	t_options;

/*
** structure to handle information of a single received packet...
** It is 'reseted' on every single loop.
*/
typedef struct s_receive
{
	int					count;
	t_msghdr			msg;
	struct sockaddr_in	peer_addr;
	struct iovec		iobuf;
	char				buf[PACKET_BUFFER_SIZE];
	int					received;
	int					type;
	t_bool				duplicated;
	t_bool				ttl_exceeded;
	t_headers			hdrs;
}	t_receive;

/*
** counts and records timed echo replies
*/
typedef struct s_timestats
{
	t_time	now;
	double	current;
	double	min;
	double	max;
	double	avg;
	double	sum_squares;
	double	variance;
}	t_timestats;

typedef struct s_counter
{
	size_t	total;
	size_t	dup;
	size_t	err;
	size_t	timed;
}	t_counter;

/*
** structure for loop statistics. Holds information of the group of
** packets sent to a specific IP.
** It is 'reseted' for each new host
*/

typedef struct s_inloop
{
	t_counter	count;
	size_t		replies;
	t_receive	recv;
	t_timestats	time;
	char		track[MAX_SEQ_TRACK];
}	t_inloop;

typedef struct s_outloop
{
	size_t				count;
	char				host[NI_MAXHOST + 1];
	char				fqdn[NI_MAXHOST + 1];
	char				packet[PACKET_BUFFER_SIZE];
	struct sockaddr_in	daddr;
}	t_outloop;

/*
** here we will create a main structure to be passed throughout the program
** keeping sockets and addresses in one single place. Maybe also unions
** to avoid casting... let's see how it goes...
** sock: the socket fd;
** pid: the program pid, used as identity;
*/
typedef struct s_ping
{
	int				sock;
	pid_t			pid;
	t_inloop		in;
	t_outloop		out;
	t_options		opts;
	t_time			begin;
	char			*program;
}	t_ping;

#endif
