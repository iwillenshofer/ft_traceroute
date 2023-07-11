/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 18:39:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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

/*
** calculates the checksum.
** best source ever: https://www.ietf.org/rfc/rfc1071.txt
*/
t_u16bits	calculate_checksum(void *buffer, size_t size)
{
	size_t		i;
	t_u8bits	*data;
	t_u32bits	sum;
	t_u16bits	last_elem;

	i = 0;
	sum = 0;
	last_elem = 0;
	data = buffer;
	if (size % 2)
	{
		size--;
		last_elem = (data[size]) << 8;
	}
	while (i < size)
	{
		sum += *(t_u16bits *)(&data[i]);
		i += 2;
	}
	if (last_elem)
		sum += (last_elem << 8);
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (~sum);
}

void	build_data(t_ping *ft_ping, char *data)
{
	size_t i;

	i = 0;
	while (i < DFL_PACKET_SIZE)
	{
		data[i] = i;
		i++;
	}
	(void)ft_ping;
}

/*
** Packet consists of icmp header + data (data size to be defined, defaults to 64)
*/
void build_packet(t_ping *ft_ping)
{
	static t_u16bits sequence = 0;
	t_icmpheader *header;
	char *data;

	if (!(ft_ping->packet))
		ft_ping->packet = malloc(sizeof(t_icmpheader) + DFL_PACKET_SIZE);
	if (!(ft_ping->packet))
		printf("MALLOC FAILED, LET'S FATALLY QUIT!!!!! ARRRRRGH!\n");
	header = (t_icmpheader*)(ft_ping->packet);
	data = (char*)(ft_ping->packet) + sizeof(t_icmpheader);
	ft_bzero(ft_ping->packet, sizeof(t_icmpheader) + DFL_PACKET_SIZE);
	header->un.echo.id = invert_bytes16((t_u16bits)ft_ping->pid);
	header->un.echo.sequence = invert_bytes16(sequence);
	header->type = ICMP_ECHO;
	header->code = 0;
	build_data(ft_ping, data);
	header->checksum = calculate_checksum(header, sizeof(t_icmpheader) + DFL_PACKET_SIZE);
	sequence++;
}

void ping(t_ping *ft_ping)
{
	struct addrinfo rcv_addr;
	unsigned char buf[1024];

	printf("IPHDR Original size: %lu, My Size: %lu.\n", sizeof(struct iphdr), sizeof(t_ipheader));
	printf("ICMP Original size: %lu, My Size: %lu.\n", sizeof(struct icmphdr), sizeof(t_icmpheader));
	while (1)
	{

		build_packet(ft_ping);
		t_u16bits check1 = checksum(ft_ping->packet, sizeof(t_icmpheader) + DFL_PACKET_SIZE);
		t_u16bits check2 = calculate_checksum(ft_ping->packet, sizeof(t_icmpheader) + DFL_PACKET_SIZE);
		printf("checksum1: %u, checksum2: %u\n", check1, check2);

		/*
		** pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));
		*/
		printf("\nSENDING HEADER!\n");

		print_icmpheader((t_icmpheader *)ft_ping->packet);

        usleep(1000000);

		if ( sendto(ft_ping->sock, ft_ping->packet, sizeof(t_icmpheader) + DFL_PACKET_SIZE, 0, ft_ping->addr_send->ai_addr, sizeof(struct sockaddr)) <= 0)
			printf("\nPacket Sending Failed!\n");

		ft_bzero(&rcv_addr, sizeof(struct addrinfo));
		ft_bzero(&buf, sizeof(buf));
		int bytes_received;
		struct sockaddr_in peerAddr;
		unsigned int len = sizeof(peerAddr);
		bytes_received = recvfrom(ft_ping->sock, &buf, sizeof(buf), 0, (struct sockaddr*)&peerAddr, &len);
		if (bytes_received > 0) {
			printf("ICMP packet received from %s\n", qualified_address(ft_ping, &(peerAddr.sin_addr)));
		printf("\nRECEIVED HEADER!\n");
		//	print_addrinfo(&rcv_addr);
	//	print_ipheader((t_ipheader *)buf);
		int ihl = ((t_ipheader *)buf)->ihl;
		print_icmpheader((t_icmpheader*)(buf + (ihl * 4)));
		}
	}     
}
