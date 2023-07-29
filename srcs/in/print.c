/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:18:30 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 13:14:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** prints the IP header for
*/
static void	print_ip(t_ip *ip)
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
** prints IP and ICMP header for --verbose (and some errors)
*/
void	print_headers(t_ping *ft_ping, t_headers *hdr)
{
	if (ft_ping->options.verbose)
	{
		dprintf(STDOUT_FILENO, "IP Hdr Dump:\n");
		ft_puthex_bytes(((char *)hdr->ip), (hdr->ip->ihl * 4), 2, 0);
	}
	if (ft_ping->options.verbose
		|| ft_ping->in.recv.hdrs.icmp->type == ICMP_SOURCE_QUENCH
		|| ft_ping->in.recv.hdrs.icmp->type == ICMP_PARAMETERPROB)
	{
		print_ip(hdr->ip);
		dprintf (STDOUT_FILENO,
			"ICMP: type %u, code %u, size %lu, id 0x%04x, seq 0x%04x\n",
			hdr->icmp->type, hdr->icmp->code,
			hdr->datalen + sizeof(t_icmp),
			ntohs(hdr->icmp->un.echo.id), ntohs(hdr->icmp->un.echo.sequence));
	}
}

/*
** Let's print all the pings!!!!
*/
void	print_echo(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "%lu bytes from %s: ",
		ft_ping->in.recv.hdrs.datalen + sizeof(t_icmp),
		inet_ntoa(ft_ping->in.recv.peer_addr.sin_addr));
	dprintf(STDOUT_FILENO, "icmp_seq=%d ttl=%d",
		ntohs(ft_ping->in.recv.hdrs.icmp->un.echo.sequence),
		ft_ping->in.recv.hdrs.ip->ttl);
	if (ft_ping->in.time.current)
		dprintf(STDOUT_FILENO, " time=%.3f ms", ft_ping->in.time.current);
	if (ft_ping->in.recv.duplicated)
		dprintf (STDOUT_FILENO, " (DUP!)");
	dprintf(STDOUT_FILENO, "\n");
}
