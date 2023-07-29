/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 07:12:16 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 01:19:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** Sets the data values right after the icmp header.
** Consists of 8 bytes of datetime, and the  rest of the 
*/
static void	build_data(t_ping *ft_ping, char *data)
{
	size_t i;
	t_time tv;
	size_t custom_size;
	size_t fill_size;

	i = 0;
	fill_size = ft_ping->options.size;
	if (fill_size >= sizeof(t_time) && !(gettimeofday(&tv, NULL)))
	{
		ft_memcpy(data, &tv, sizeof(t_time));
		data += sizeof(t_time);
		fill_size -= sizeof(t_time);
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
	t_icmp *header;
	char *data;
	size_t package_size;

	ft_bzero(ft_ping->out.packet, sizeof(ft_ping->out.packet));
	package_size = sizeof(t_icmp) + ft_ping->options.size;
	header = (t_icmp*)(ft_ping->out.packet);
	data = (char*)(ft_ping->out.packet) + sizeof(t_icmp);
	header->un.echo.id = htons(ft_ping->pid);
	header->un.echo.sequence = htons(ft_ping->out.count);
	clear_duptrack(ft_ping, ft_ping->out.count);
	header->type = ICMP_ECHO;
	header->code = 0;
	build_data(ft_ping, data);
	header->checksum = checksum(header, package_size);
}
void	ping_out(t_ping *ft_ping)
{
	build_packet(ft_ping);
	if ( sendto(ft_ping->sock, ft_ping->out.packet, sizeof(t_icmp) + ft_ping->options.size, 0, (struct sockaddr *)&(ft_ping->out.daddr), sizeof(struct sockaddr)) <= 0)
		printf("\nWE'VE GOT A FATAL ERROR HERE. ADJUST.");
	else
		ft_ping->out.count++;
}
