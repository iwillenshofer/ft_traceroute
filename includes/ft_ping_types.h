/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:15 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 01:21:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping_parse.h"

#ifndef FT_PING_TYPES_H
# define FT_PING_TYPES_H

# define ERROR_BUFFER_SIZE 			64
# define DFL_PACKET_SIZE 			56
# define DFL_CUSTOM_PATTERN_SIZE 	16
# define DFL_TTL					64
# define MAX_PACKET_SIZE			65399
# define PACKET_BUFFER_SIZE			65535
# define MAX_SEQ_TRACK				128
# define MAX_PATTERN				31
# define NI_MAXHOST     			1025

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

struct s_ping;

typedef struct s_lstopt
{
	char	shortcut;
	int		type;
	char	fullname[16];
	char	desc[128];
	void	(*handler)(struct s_ping *, struct s_lstopt *opt, char *val);
}	t_lstopt;

typedef enum e_bool {false, true}	t_bool;
typedef struct timeval	t_time;

/*
** define unsigned 8, 16 and 32 bits variables. Those are
** system defined as __be16, __be32... but I'm defining it myself
** for learning purposes, testing and reference.
** for 32bits systems, 32bits should be unsigned long instead of
** int, but I didn't implement it as I found unecessary for this project.
*/
typedef unsigned char		t_u8bits;
typedef unsigned short		t_u16bits;
typedef unsigned int		t_u32bits;

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

typedef struct s_headers {
	t_ip		*ip;
	t_icmp	*icmp;
	char			*data;
	size_t			data_size;
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

typedef struct msghdr t_msghdr;

/*
** options for all kinds of requests
*/

typedef struct s_options_pattern
{
	t_u8bits	pattern[DFL_CUSTOM_PATTERN_SIZE];
	t_u8bits	size;
}	t_options_pattern;

typedef struct s_options
{
	t_bool				flood;
	t_bool				quiet;
	t_u8bits			preload;
	t_options_pattern	pattern;
	t_u16bits			size;	
	t_u8bits			count;
	t_u8bits			interval;
	t_bool				numeric;
	t_u8bits			ttl;
	t_bool				verbose;
	t_u8bits			timeout;
	t_lstopt			available[OPT_LSTSIZE];
}	t_options;

/*
** structure to handle information of a single received packet...
** It is 'reseted' on every single loop.
*/
typedef struct s_receive
{
	int count;
	t_msghdr			msg;
	struct sockaddr_in	peer_addr;
	struct iovec		iobuf;
	char				buf[MAX_PACKET_SIZE];
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
	size_t count;
	char			host[NI_MAXHOST + 1];
	char			fqdn[NI_MAXHOST + 1];
	char			packet[PACKET_BUFFER_SIZE];
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
	t_options		options;
	char			*program;
}	t_ping;

#endif
