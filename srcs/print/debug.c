/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:18:30 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 01:01:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** prints the IP header for debugging
*/
void	print_ip(t_ip *ip)
{
	dprintf(STDOUT_FILENO,
		"Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	dprintf(STDOUT_FILENO,
		" %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x ",
		ip->version, ip->ihl, ip->tos, ntohs(ip->tot_len), ntohs(ip->id),
		(ntohs(ip->frag_off) & 0b1110000000000000) >> 13,
		ntohs(ip->frag_off) & 0b0000111111111111,
		ip->ttl, ip->protocol, ntohs(ip->check));
	dprintf(STDOUT_FILENO, "%s  ",
		inet_ntoa(*(t_inaddr *)(&(ip->saddr))));
	dprintf(STDOUT_FILENO, "%s ",
		inet_ntoa(*(t_inaddr *)(&(ip->daddr))));
	if (ip->ihl * 4 > sizeof(t_ip))
		ft_puthex_bytes(((char *)ip) + sizeof(t_ip),
			(ip->ihl * 4) - sizeof(t_ip), 0, 0);
	dprintf(STDOUT_FILENO, "\n");
}

/*
** prints the UDP header for debugging
*/
void print_icmp (t_icmp *icmp)
{
	dprintf (STDOUT_FILENO,
		"ICMP: type %u, code %u, id 0x%04x, seq 0x%04x\n",
		icmp->type, icmp->code,
		ntohs(icmp->un.echo.id), ntohs(icmp->un.echo.sequence));
}

/*
** prints the UDP header for debugging
*/
void	print_udp(t_udp *udp)
{
	dprintf(STDOUT_FILENO,
		"src_port dst_port dgram_len dgram_cksum\n");
	dprintf(STDOUT_FILENO,
		" %u %u %02x %02x\n",
		ntohs(udp->source),
		ntohs(udp->dest),
		ntohs(udp->len),
		ntohs(udp->check));
}
