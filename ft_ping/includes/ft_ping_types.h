/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:15 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/18 15:16:00 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_TYPES_H
# define FT_PING_TYPES_H

# define ERROR_BUFFER_SIZE 64
# define DFL_PACKET_SIZE 56
# define DFL_CUSTOM_PATTERN_SIZE 16
# define DFL_TTL 64
# define MAX_PACKET_SIZE 65535
# define MAX_SEQ_TRACK 4


typedef enum e_bool {false, true}	t_bool;
typedef struct timeval	t_time;

/*
** define unsigned 8, 16 and 32 bits variables. Those are
** system defined as __be16, __be32... but I'm defining it myself
** for learning purposes, testing and reference.
*/
typedef unsigned char		t_u8bits;
typedef unsigned short		t_u16bits;

# ifdef __x86_64__

typedef unsigned int		t_u32bits;

# else

typedef unsigned long		t_u32bits;

# endif

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

typedef struct iphdr	t_ipheader;

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
*/

typedef struct icmphdr	t_icmpheader;

/*
** simple struct to parse buffer into, and make it easier to access
** ip and icmp headers, as well as data, without having to do multiple
** casting
*/
typedef struct s_headers {
	t_ipheader		*ip;
	t_icmpheader	*icmp;
	char			*data;
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
typedef struct s_options_all
{
	t_u8bits	count;
	t_bool		debug;
	t_u8bits	interval;
	t_bool		numeric;
	t_bool		ignore_routing;
	t_u8bits	ttl;
	t_u16bits	tos;
	t_bool		verbose;
	t_u8bits	timeout;
	t_u8bits	linger;	
}	t_options_all;

typedef struct s_options_pattern
{
	t_u8bits	pattern[DFL_CUSTOM_PATTERN_SIZE];
	t_u8bits	size;
}	t_options_pattern;

/*
** options specific for echo replies
*/
typedef struct s_options_echo
{
	t_bool				flood;
	t_u8bits			ip_timestamp;
	t_u8bits			preload;
	t_options_pattern	pattern;
	t_bool				quiet;
	t_bool				route;
	t_u16bits			size;	
}	t_options_echo;

typedef struct s_options
{
	t_u8bits		request_type;
	t_options_all	all;
	t_options_echo	echo;
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
}	t_receive;

/*
** time statistics. t_bool record is set to define
** wether these stats are recorded or not, depending on the
** size of the data received (wether we have a timestamp or not).
*/
typedef struct s_timestats
{
	t_bool	record;
	double	min;
	double	max;
	double	avg;
	double	stddev;
}	t_timestats;


/*
** structure for loop statistics. Holds information of the group of
** packets sent to a specific IP.
** It is 'reseted' for each new host
*/
typedef struct s_inloop
{
	size_t		count;
	t_receive	recv;
	t_timestats	time;
	char		track[MAX_SEQ_TRACK];
}	t_inloop;

typedef struct s_outloop
{
	size_t count;

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


	t_icmpheader	*packet; //OK
	t_options		options; //OK
	char			*program; // stores the first line of argv
	struct addrinfo	*addr_send;
	struct addrinfo	addr_recv;
	char			error[ERROR_BUFFER_SIZE];
	char			raw_host[HOST_NAME_MAX]; // the original hostname that we are trying to ping
	char			qualified_address[(HOST_NAME_MAX * 2) + 4];
}	t_ping;

#endif
