/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorwillenshofer <igorwillenshofer@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:17:18 by iwillens          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/26 17:24:52 by igorwillens      ###   ########.fr       */
=======
/*   Updated: 2023/06/14 09:47:23 by iwillens         ###   ########.fr       */
>>>>>>> 9cbf17f137ce183b7bb9b37a862f2ebe26e36598
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
/*
** allowed functions:
** gettimeofday.
** exit.
** inet_ntop. / inet_pton.
** signal / alarm.
** socket / setsockopt.
** sendto / recvmsg.
** getpid / getuid.
** getaddrinfo / freeaddrinfo.
** strerror / gai_strerror.
** printf and its family.
*/

/*
** socket
** int socket(int domain, int type, int protocol);
*/

/*
PING USES ICMP: RFC 792
https://datatracker.ietf.org/doc/html/rfc792
*/

#include <stdio.h>


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

	int getaddrinfo(const char *node, const char *service,
						const struct addrinfo *hints,
						struct addrinfo **res);
*/


void print_addrinfo(struct addrinfo *head)
{
	char str[INET_ADDRSTRLEN];
		
	printf("struct addrinfo {\n"); 
	printf("	int		ai_flags = %d;\n", head->ai_flags); 
	printf("	int		ai_family = %d;\n", head->ai_family); 
	printf("	int		ai_socktype = %d;\n", head->ai_socktype); 
	printf("	int		ai_protocol = %d;\n", head->ai_protocol); 
	printf("	socklen_t	ai_addrlen = %lu;\n", (size_t)(head->ai_addrlen)); 
	printf("	struct sockaddr	*ai_addr {\n"); 
	printf("		sa_family = %d;\n", head->ai_addr->sa_family); 
	inet_ntop(AF_INET, &((struct sockaddr_in *)head->ai_addr)->sin_addr, str, INET_ADDRSTRLEN);
	printf("		sa_data = %s;\n", str);
	printf("	};\n"); 
	printf("	char            *ai_canonname = %s;\n", head->ai_canonname); 
	printf("	struct addrinfo *ai_next = %p;\n", head->ai_next); 
	printf("};\n"); 
}

struct addrinfo *get_address(void)
{
	struct addrinfo hints;
	struct addrinfo *res;

	res = NULL;
	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if(getaddrinfo("google.com", NULL, &hints, &res))
	{
		printf("problem resolving address\n");	
	}
	else
	{
		print_addrinfo(res);
	}
	return (res);
}

int	opensocket(void)
{	

<<<<<<< HEAD
	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	printf("socket: %d\n", fd);
	return (fd);
}
/*
struct icmphdr {
	__u8      type;
	__u8      code;
	__sum16   checksum;
	union {
		struct {
			__be16  id;
			__be16  sequence;
		} echo;
		__be32  gateway;
		struct {
			__be16  __unused;
			__be16  mtu;
		} frag;
	} un;
};
*/
unsigned short checksum(void *b, int len)
{    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;
 
    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}
 
struct ping_pkt
{
    struct icmphdr hdr;
    char msg[64 - sizeof(struct icmphdr)];
};
 
void send_ping(int sock, struct addrinfo* address)
{
	struct ping_pkt pkt;
	struct addrinfo rcv_addr;
	socklen_t addrlen;
	int ttl_val=64;
    struct timeval tv_out;
    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;


	struct sockaddr_in ping_addr;


	setsockopt(sock, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof tv_out);

	ft_bzero(&ping_addr, sizeof(struct sockaddr_in));
	ping_addr.sin_family = address->ai_family;
	ping_addr.sin_addr.s_addr = ((struct sockaddr_in *)address->ai_addr)->sin_addr.s_addr;
	int seq = 0;
	while (1)
	{
		ft_bzero(&pkt, sizeof(pkt));
		pkt.hdr.type = ICMP_ECHO;
		pkt.hdr.un.echo.id = getpid();
		int i;
		for (i = 0; i < (int)(sizeof(pkt.msg)) - 1; i++ )
				pkt.msg[i] = i + '0';
		pkt.msg[i] = 0;
		pkt.hdr.un.echo.sequence = seq++;
		pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));

        usleep(1000000);

		if ( sendto(sock, &pkt, sizeof(pkt), 0,  (struct sockaddr*) &ping_addr, sizeof(struct sockaddr)) <= 0)
			printf("\nPacket Sending Failed!\n");

		addrlen = sizeof(rcv_addr);
		if ( recvfrom(sock, &pkt, sizeof(pkt), 0, (struct sockaddr*)&rcv_addr, &addrlen) <= 0)
			printf("\nPacket receive failed!\n");
		else
			printf("\nSeems to be OK\n");
	}     

}

int	main(void)
{
	struct addrinfo *res;
	res = get_address();
	int fd = opensocket();
	send_ping(fd, res);
	close(fd);
	freeaddrinfo(res); 
=======
	printf("platform %d \n", THISISAMAC);
>>>>>>> 9cbf17f137ce183b7bb9b37a862f2ebe26e36598
	return (0);
}
