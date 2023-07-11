/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:05:18 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:29:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
# include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/time.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	_print_hex_byte(unsigned char c)
{
	if (c < 10)
		c += '0';
	else
		c += 'a' - 10;
	ft_putchar(c);
}

void	ft_puthexbyte(unsigned char c)
{
	unsigned char	n1;
	unsigned char	n2;

	n1 = c / 16;
	n2 = c % 16;
	ft_putchar(' ');
	_print_hex_byte(n1);
	_print_hex_byte(n2);
}


void	print_bits(unsigned char byte)
{
	size_t i;
	size_t size;

	i = 0;
	size = 8;
	while (i < size)
	{
		if ((byte & (0b10000000 >> i)))	
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i++;
	}
}

/*
** size in bytes. use with sizeof()
*/
void	print_bytes(void *bytes, size_t size)
{
	char *s;
	size_t i;

	i = 0;
	s = bytes;
	while (i < size)
	{
		print_bits(s[i]);
		i++;
		write(1, " ", 1);
		if (i && !(i % 32))
			write(1, "\n", 1);
		else if (!(i % 4))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

/*
** size in bytes. use with sizeof()
*/
void	print_hex(void *bytes, size_t size)
{
	char *s;
	size_t i;

	i = 0;
	s = bytes;
	while (i < size)
	{
		ft_puthexbyte(s[i]);
		i++;
		write(1, " ", 1);
		if (i && !(i % 32))
			write(1, "\n", 1);
		else if (!(i % 4))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

#define MAX_CLIENTS 128    // Maximum number of client connections allowed
#define BUFFER_SIZE 200000 // Size of the buffer used for message exchange

void print_ethernet(struct ethhdr *head)
{
	static int count = 0;
  printf("struct ethhdr %d{\n", count++);
  printf("    unsigned char   h_dest[ETH_ALEN]; %.*s\n", ETH_ALEN, head->h_dest);
  printf("    unsigned char   h_source[ETH_ALEN]; %.*s\n", ETH_ALEN, head->h_source);
  printf("    __be16      h_proto; %u\n", head->h_proto);
  printf("} __attribute__((packed));\n");
}

void print_ipheader(struct iphdr *head)
{
	printf("struct iphdr {");
    printf("    __u8    ihl:4 = %d\n", head->ihl);
	printf("    __u8	version:4 = %d\n", head->version);
    printf("    __u8    tos = %d\n", head->tos);
    printf("    __be16  tot_len = %d\n", head->tot_len);
    printf("    __be16  id = %d\n", head->id);
    printf("    __be16  frag_off = %d\n", head->frag_off);
    printf("    __u8    ttl = %d\n", head->ttl);
    printf("    __u8    protocol = %d\n", head->protocol);
    printf("    __sum16 check = %d\n", head->check);  
	printf("    __be32  saddr = %d\n", head->saddr);
    printf("    __be32  saddr = %d.%d.%d.%d\n", (0xff & head->saddr), (0xff00 & head->saddr) >> 8 , (0xff0000 & head->saddr) >> 16, (0xff000000 & head->saddr) >> 24);
	printf("    __be32  daddr = %d\n", head->daddr);
	printf("    __be32  daddr = %d.%d.%d.%d\n", (0xff & head->daddr), (0xff00 & head->daddr) >> 8 , (0xff0000 & head->daddr) >> 16, (0xff000000 & head->daddr) >> 24);
	printf("}\n");
}


void print_icmpheader(struct icmphdr *head)
{
	printf("struct icmphdr {\n");
	printf("__u8		type = %d;\n", head->type);
	printf("__u8		code = %d;\n", head->code);
	printf("__sum16	checksum = %d;\n", head->checksum);
	printf("union {\n");
	printf("	struct {\n");
	printf("		__be16	id = %d;\n", head->un.echo.id);
	printf("		__be16	sequence = %d;\n", head->un.echo.sequence);
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

ssize_t format_timeval(struct timeval *tv, char *buf, size_t sz)
{
  ssize_t written = -1;
  struct tm *gm = gmtime(&tv->tv_sec);

  if (gm)
  {
    written = (ssize_t)strftime(buf, sz, "%Y-%m-%dT%H:%M:%S", gm);
    if ((written > 0) && ((size_t)written < sz))
    {
      int w = snprintf(buf+written, sz-(size_t)written, ".%06dZ", (int)(tv->tv_usec));
      written = (w > 0) ? written + w : -1;
    }
  }
  return written;
}

typedef	struct s_options {
	char type;
	char type2;
	char type3;
	char type4;
}	t_options;

void print_option(t_options *head)
{
	printf("struct t_option {\n");
	printf("__u8  type = %d;\n", head->type);
	printf("__u8  type = %d;\n", head->type2);
	printf("__u8  type = %d;\n", head->type3);
	printf("__u8  type = %d;\n", head->type4);

	printf("};\n");
	(void)head;
}

void bytes(unsigned int byte)
{
	size_t i = 0;
	

	unsigned int mask;
	mask = (0b1 << ((sizeof(unsigned int) * 8) - 1));
	while (i < (sizeof(unsigned int) * 8))
	{
		write(1, ((mask >> i) & (byte) ? "1": "0"), 1);
		i++;
		if (!(i % 8))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void printbytes(unsigned int *v, size_t size_in_4bytes)
{
//	printf("\n%lu bytes: \n", size_in_4bytes * 4);
	size_t j = 0;
	while (j < size_in_4bytes)
	{
		bytes(*v);
		v++;
		j++;
	}
}

int main(int argc, char **argv) 
{
	static int count = 0;
	(void)argc;
	(void)argv;
//	unsigned int X = 0;
//	while (X++ < UINT_MAX)
//		printbytes(&(X), 1);
//	return 0;
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
//	int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	int bytes_received;
	unsigned char buf[1024];
	struct sockaddr_in peerAddr;
	unsigned int len = sizeof(peerAddr);
	bzero(&buf, sizeof(buf));
	while ((bytes_received = recvfrom(sock, &buf, sizeof(buf), 0, (struct sockaddr*)&peerAddr, &len)))
	{

//		unsigned int protocol =  ((struct iphdr *)(buf  + sizeof(struct ethhdr)))->protocol;
//		if (protocol == 6)
//			continue;
		if (*(uint16_t *)"\0\xff" > 0x100)
			((struct iphdr *)(buf))->tot_len = ((((struct iphdr *)(buf))->tot_len  & 0xff) << 8) | ((((struct iphdr *)(buf))->tot_len  & 0xff00) >> 8);
		unsigned int tot_len =  ((struct iphdr *)(buf))->tot_len;
		if (count > 3000)
			exit(0);
		unsigned int ihl =  ((struct iphdr *)(buf))->ihl;
		unsigned int headers_len = (ihl * 4) + sizeof(struct icmphdr);
		struct icmphdr* icmp = (struct icmphdr *)(buf + (ihl * 4));
		char *info = (char*)(buf + headers_len);
		printf("\n\n\n\n tot_len: %d, header len: %d, icmp->type: %u, icmp->code: %u, icmp->checksum: %u, icmp->id: %u, icmp->seq: %u\n", tot_len, headers_len, (icmp->type),htons(icmp->code),htons(icmp->checksum), htons(icmp->un.echo.id), htons(icmp->un.echo.sequence));
		print_hex(info, tot_len - headers_len);
		print_bytes(info, tot_len - headers_len);
		write(1, "\n", 1);
		//is this a timestamp????
		struct timeval timestamp;
		memcpy(&timestamp, info, sizeof(timestamp));
		timestamp.tv_sec = (timestamp.tv_sec);
		timestamp.tv_usec = (timestamp.tv_usec);
		char buf[28];
		bzero(buf, sizeof(buf));
		format_timeval(&timestamp, buf, sizeof(buf));
		printf("timestamp has %lu bytes\n", sizeof(timestamp));
		printf("%s \n", buf);

//
//		write(1, info, tot_len - headers_len);
		write(1, "\n", 1);
		if (ihl)
		{
	//		print_ethernet((struct ethhdr *)(buf));
	//		print_ipheader((struct iphdr *)(buf));
	//		if ((ihl * 4) > sizeof(struct iphdr))
	//			print_option((t_options *)(buf + (sizeof(struct iphdr)  + sizeof(struct ethhdr))));
	//		print_icmpheader((struct icmphdr *)(buf  + (ihl * 4)));
//			unsigned int i = 5; //min size of IHL.
//			while (i < ihl)
//			{
//				printbytes((unsigned int *)(buf + (i * 4)), 1);
//				i++;
//			}
//			printf("ip header\n");
//			printbytes((unsigned int  *)(buf), ihl);
//			printf("icmp header\n");
//			printbytes((unsigned int  *)(buf + (ihl * 4)), 2);
		}
		bzero(&buf, sizeof(buf));
	};
    return 0;
}
