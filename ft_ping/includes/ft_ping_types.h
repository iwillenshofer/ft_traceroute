/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:15 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:06:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_TYPES_H
# define FT_PING_TYPES_H

# define ERROR_BUFFER_SIZE 64
# define DFL_PACKET_SIZE 65

typedef enum e_bool {false, true}	t_bool;

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
*/

typedef struct s_ipheader
{
	t_u8bits		ihl: 4;
	t_u8bits		version: 4;
	t_u8bits		tos;
	t_u16bits		tot_len;
	t_u16bits		id;
	t_u16bits		frag_off;
	t_u8bits		ttl;
	t_u8bits		protocol;
	t_u16bits		checksum;
	unsigned int	saddr;
	unsigned int	daddr;
}	t_ipheader;

/*
** since we will only be using the IP header on the way in (I suppose,
** maybe I'm brave enough to implement it on the way OUT too, instead of
** letting the socket do it for me, but we'll cross that bridge later),
** options must be implemented, even though they will *probably* not be
** be read by our program.
** The options structure may be implemented right after the ipheader
** and right before the icmp header. That means that the ihl (Internet
** Header Length) must be checked to determine the position of icmp
** header in the buffer.
** If, the options are found to be irrelevant to this project, I'll
** just ignore them, removing this structure and calculate the start of
** icmp header using ihl, ignoring what is "in between".
*/

typedef	struct s_options
{
	unsigned int	faddr;
	t_u8bits	optlen;
	t_u8bits	srr;
	t_u8bits	rr;
	t_u8bits	ts;
	t_u8bits	is_setbyuser:1;
	t_u8bits	is_data:1;
	t_u8bits	is_strictroute:1;
	t_u8bits	srr_is_hit:1;
	t_u8bits	is_changed:1;
	t_u8bits	rr_needaddr:1;
	t_u8bits	ts_needtime:1;
	t_u8bits	ts_needaddr:1;
	t_u8bits	padding[4];
}	t_ipoptions;

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
** The below implementation considers all kinds of icmp messages.
** If, by the end of this project, just ECHO and ECHO REPLY are needed
** and the rest of the messages are not used for checking for errors,
** this header will be simplified and the union removed.
*/

typedef struct s_icmpheader
{
	t_u8bits			type;
	t_u8bits			code;
	t_u16bits			checksum;
	union	u_un
	{
		struct	s_echo
		{
			t_u16bits	id;
			t_u16bits	sequence;
		}	echo;
		unsigned int		gateway;
		struct	s_frag
		{
			t_u16bits	reserved;
			t_u16bits	mtu;
		}	frag;
	} un;	
}	t_icmpheader;

//we may need to change it into a pointer for variable info
typedef struct s_packet {
	t_icmpheader	hdr;
	char			data[DFL_PACKET_SIZE - sizeof(t_icmpheader)];
}	t_packet;

typedef char	t_flag;

typedef struct s_flag_opt
{
	char	enabled;
	char	ttl;
}	t_flag_opt;

typedef struct s_flags
{
	t_flag	verbose;
	t_flag	help;
}	t_flags;

/*
** here we will create a main structure to be passed throughout the program
** keeping sockets and addresses in one single place. Maybe also unions
** to avoid casting... let's see how it goes...
*/

typedef struct s_ping
{
	int				sock;
	pid_t			pid;
	char			qualified_address[HOST_NAME_MAX];
	char			*program; // stores the first line of argv
	char			error[ERROR_BUFFER_SIZE];
	char			*raw_host; // the original hostname that we are trying to ping
	char			*inet_ntop; //The buffer dst must be at least INET_ADDRSTRLEN bytes long. lets do this on STACK, shall we?
	char			*inet_name;
	struct addrinfo	*addr_send;
	struct addrinfo	addr_recv;
	t_icmpheader	*packet;
	t_flags		flags; // maybe a pointer? maybe a linkedlist?
}	t_ping;

#endif
