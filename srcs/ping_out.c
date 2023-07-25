/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:16 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 21:48:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	build_data(t_ping *ft_ping, char *data)
{
	size_t i;
	struct timeval tv;
	size_t custom_size;
	size_t fill_size;

	i = 0;
	fill_size = ft_ping->options.size;
	if (fill_size >= sizeof(struct timeval) && !(gettimeofday(&tv, NULL)))
	{
		ft_memcpy(data, &tv, sizeof(struct timeval));
		data += sizeof(struct timeval);
		fill_size -= sizeof(struct timeval);
	}
	custom_size = ft_ping->options.pattern.size;
	while (i < fill_size)
	{
		if (custom_size)
			data[i] = ft_ping->options.pattern.pattern[i % custom_size];
		else
			data[i] = i % (0xff + 1);
		i++;
	}
}

/*
** Packet consists of icmp header + data (data size to be defined, defaults to 56)
** ICMP header + default size = 64.
*/
static void build_packet(t_ping *ft_ping)
{
	t_icmpheader *header;
	char *data;
	size_t package_size;

	package_size = sizeof(t_icmpheader) + ft_ping->options.size;
	if (!(ft_ping->packet))
		ft_ping->packet = malloc(package_size);
	if (!(ft_ping->packet))
		printf("MALLOC FAILED, LET'S FATALLY QUIT!!!!! ARRRRRGH!\n");
	header = (t_icmpheader*)(ft_ping->packet);
	data = (char*)(ft_ping->packet) + sizeof(t_icmpheader);
	ft_bzero(ft_ping->packet, package_size);
	header->un.echo.id = htons(ft_ping->pid);
	header->un.echo.sequence = htons(ft_ping->out.count);
	header->type = ICMP_ECHO;
	header->code = 0;
	build_data(ft_ping, data);
	header->checksum = checksum(header, package_size);
}
#include <errno.h>
void	ping_out(t_ping *ft_ping)
{
	build_packet(ft_ping);
//	print_icmpheader((t_icmpheader *)ft_ping->packet);
	if ( sendto(ft_ping->sock, ft_ping->packet, sizeof(t_icmpheader) + ft_ping->options.size, 0, ft_ping->addr_send->ai_addr, sizeof(struct sockaddr)) <= 0)
		printf("\nPacket Sending Failed!: %s\n",strerror(errno));
	else
		ft_ping->out.count++;
}
