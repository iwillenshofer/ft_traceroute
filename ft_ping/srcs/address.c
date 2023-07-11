/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 08:52:05 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:58:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <limits.h>

/*
	struct addrinfo {
		int              ai_flags;
		int              ai_family;
		int              ai_socktype;
		int              ai_protocol;
		socklen_t        ai_addrlen;
		struct sockaddr *ai_addr;
		char            *ai_canonname;
		struct addrinfo *ai_next;
	};

	struct sockaddr {
		unsigned short    sa_family;    // address family, AF_xxx
		char              sa_data[14];  // 14 bytes of protocol address
	}; 

	sockaddr is a generic structure. Can be converted to sockaddr_in,
	sockaddr_in6, sockaddr_un, and so on... Since we are using IPV4,
	we will deal with it as sockaddr_in using a cast.

	struct sockaddr_in {
		short            sin_family;   // e.g. AF_INET
		unsigned short   sin_port;     // e.g. htons(3490)
		struct in_addr   sin_addr;     // see struct in_addr, below
		char             sin_zero[8];  // zero this if you want to
	};

	struct in_addr {
		unsigned long s_addr;  // load with inet_aton()
	};

	int getaddrinfo(const char *node, const char *service,
						const struct addrinfo *hints,
						struct addrinfo **res);
*/




/*
** struct iphdr {
     __u8    ihl:4, version:4;
     __u8    tos;
     __be16  tot_len;
     __be16  id;
     __be16  frag_off;
     __u8    ttl;
     __u8    protocol;
     __sum16 check;
     __be32  saddr;
     __be32  daddr;
 };

struct icmphdr {
  __u8		type;
  __u8		code;
  __sum16	checksum;
  union {
	struct {
		__be16	id;
		__be16	sequence;
	} echo;
	__be32	gateway;
	struct {
		__be16	__unused;
		__be16	mtu;
	} frag;
  } un;
};

*/

void	print_icmptype(int type)
{
	if (type == ICMP_ECHOREPLY)
		printf("ICMP_ECHOREPLY\n");
	else if (type == ICMP_DEST_UNREACH)
		printf("ICMP_DEST_UNREACH\n");
	else if (type == ICMP_SOURCE_QUENCH)
		printf("ICMP_SOURCE_QUENCH\n");
	else if (type == ICMP_REDIRECT)
		printf("ICMP_REDIRECT\n");
	else if (type == ICMP_ECHO)
		printf("ICMP_ECHO\n");
	else if (type == ICMP_TIME_EXCEEDED)
		printf("ICMP_TIME_EXCEEDED\n");
	else if (type == ICMP_PARAMETERPROB)
		printf("ICMP_PARAMETERPROB\n");
	else if (type == ICMP_TIMESTAMP)
		printf("ICMP_TIMESTAMP\n");
	else if (type == ICMP_TIMESTAMPREPLY)
		printf("ICMP_TIMESTAMPREPLY\n");
	else if (type == ICMP_INFO_REQUEST)
		printf("ICMP_INFO_REQUEST\n");
	else if (type == ICMP_INFO_REPLY)
		printf("ICMP_INFO_REPLY\n");
	else if (type == ICMP_ADDRESS)
		printf("ICMP_ADDRESS\n");
	else if (type == ICMP_ADDRESSREPLY)
		printf("ICMP_ADDRESSREPLY\n");
	else
		printf("unknown type: %d\n", type);
}

void print_icmpheader(t_icmpheader *head)
{
	printf("struct icmphdr {\n");
	printf("__u8		type = %d: ", head->type);
	print_icmptype(head->type);
	printf("__u8		code = %d;\n", head->code);
	printf("__sum16	checksum = %d;\n", bytes16_le(head->checksum));
	printf("union {\n");
	printf("	struct {\n");
	printf("		__be16	id = %d;\n", bytes16_le(head->un.echo.id));
	printf("		__be16	sequence = %d;\n", bytes16_le(head->un.echo.sequence));
	printf("	} echo;\n");
	printf("	__be32	gateway = %d;\n", head->un.gateway);
	printf("	struct {\n");
	printf("		__be16	__unused = %d;\n", 0);
	printf("		__be16	mtu = %d;\n", head->un.frag.mtu);
	printf("	} frag;\n");
	printf("} un;\n");
	printf("};\n");
	(void)head;
}

void print_ipheader(t_ipheader *head)
{
	printf("struct iphdr {");
//  printf("    __u8    ihl:4 = %d\n", head->ihl);
//	printf("    __u8	version:4 = %d\n", head->version);
    printf("    __u8    tos = %d\n", head->tos);
    printf("    __be16  tot_len = %d\n", head->tot_len);
    printf("    __be16  id = %d\n", head->id);
    printf("    __be16  frag_off = %d\n", head->frag_off);
    printf("    __u8    ttl = %d\n", head->ttl);
    printf("    __u8    protocol = %d\n", head->protocol);
    printf("    __sum16 check = %d\n", head->checksum);  
	printf("    __be32  saddr = %d\n", head->saddr);
    printf("    __be32  saddr = %d.%d.%d.%d\n", (0xff & head->saddr), (0xff00 & head->saddr) >> 8 , (0xff0000 & head->saddr) >> 16, (0xff000000 & head->saddr) >> 24);
	printf("    __be32  daddr = %d\n", head->daddr);
	printf("    __be32  daddr = %d.%d.%d.%d\n", (0xff & head->daddr), (0xff00 & head->daddr) >> 8 , (0xff0000 & head->daddr) >> 16, (0xff000000 & head->daddr) >> 24);
	printf("}\n");
}

void print_addrinfo(struct addrinfo *head)
{
	char str[INET_ADDRSTRLEN];
		
	printf("struct addrinfo %i{\n", INET_ADDRSTRLEN); 
	printf("	int		ai_flags = %d;\n", head->ai_flags); 
	printf("	int		ai_family = %d;\n", head->ai_family); 
	printf("	int		ai_socktype = %d;\n", head->ai_socktype); 
	printf("	int		ai_protocol = %d;\n", head->ai_protocol); 
	printf("	socklen_t	ai_addrlen = %lu;\n", (size_t)(head->ai_addrlen)); 
	printf("	struct sockaddr	*ai_addr {\n"); 
	if (head->ai_addr)
	{
		printf("		sa_family = %d;\n", head->ai_addr->sa_family); 
		inet_ntop(AF_INET, &((struct sockaddr_in *)head->ai_addr)->sin_addr, str, INET_ADDRSTRLEN);
		printf("		sa_data = %s;\n", str);
	}
	printf("	};\n"); 
	printf("	char            *ai_canonname = %s;\n", head->ai_canonname); 
	printf("	struct addrinfo *ai_next = %p;\n", head->ai_next); 
	printf("};\n"); 
}

/*
** gets information on address to be ping'ed (host) and stores
**  into ft_ping->addr_send, to be used by ping().
*/
void	get_address(t_ping *ft_ping)
{
	struct addrinfo hints;

	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_flags = AI_CANONNAME;
	if(getaddrinfo(ft_ping->raw_host, NULL, &hints, &(ft_ping->addr_send)))
		fatal(ft_ping,
			get_errorstr(ft_ping, ERROR_UNKNOWN_HOST, ft_ping->program, ft_ping->raw_host), true);
	if (ft_ping->addr_send->ai_canonname)
		ft_ping->raw_host = ft_ping->addr_send->ai_canonname;
	print_addrinfo(ft_ping->addr_send);
}

/*
int reverse_lookup(void)
{
	struct addrinfo *addr = get_address();
	struct sockaddr *socket_addr = addr->ai_addr;
	struct sockaddr_in *socket_internet_addr = (struct sockaddr_in *)socket_addr;
	struct in_addr *internet_addr = &(socket_internet_addr->sin_addr);

	inetname(internet_addr);

	return (0);
}
*/

#if !BONUS

char *qualified_address(t_ping *ft_ping, struct in_addr *in)
{
	(void)in;
	ft_bzero(ft_ping->qualified_address, sizeof(ft_ping->qualified_address));
	sprintf(ft_ping->qualified_address, "(%s) %s", ft_ping->raw_host , inet_ntoa(*in));
	return (ft_ping->qualified_address);
}

#endif
