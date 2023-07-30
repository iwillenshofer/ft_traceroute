/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noecho.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:44:30 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 09:54:42 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	print_unreach(size_t code)
{
	char	*buf[NR_ICMP_UNREACH + 1];

	ft_bzero(buf, sizeof(buf));
	buf[ICMP_NET_UNREACH] = "Destination Net Unreachable";
	buf[ICMP_HOST_UNREACH] = "Destination Host Unreachable";
	buf[ICMP_PROT_UNREACH] = "Destination Protocol Unreachable";
	buf[ICMP_PORT_UNREACH] = "Destination Port Unreachable";
	buf[ICMP_FRAG_NEEDED] = "Fragmentation needed and DF set";
	buf[ICMP_SR_FAILED] = "Source Route Failed";
	buf[ICMP_NET_UNKNOWN] = "Network Unknown";
	buf[ICMP_HOST_UNKNOWN] = "Host Unknown";
	buf[ICMP_HOST_ISOLATED] = "Host Isolated";
	buf[ICMP_NET_UNR_TOS] = "Destination Network Unreachable At This TOS";
	buf[ICMP_HOST_UNR_TOS] = "Destination Host Unreachable At This TOS";
	buf[ICMP_PKT_FILTERED] = "Packet Filtered";
	buf[ICMP_PREC_VIOLATION] = "Precedence Violation";
	buf[ICMP_PREC_CUTOFF] = "Precedence Cutoff";
	if (code <= NR_ICMP_TYPES && buf[code])
		dprintf(STDOUT_FILENO, buf[code]);
	else
		dprintf(STDOUT_FILENO, "Dest Unreachable, Unknown Code: %lu", code);
}

static void	print_common(size_t type, size_t code)
{
	char	*buf[ICMP_REDIR_HOSTTOS + 1];

	ft_bzero(buf, sizeof(buf));
	buf[ICMP_REDIR_NET] = "Redirect Network";
	buf[ICMP_REDIR_HOST] = "Redirect Host";
	buf[ICMP_REDIR_NETTOS] = "Redirect Type of Service and Network";
	buf[ICMP_REDIR_HOSTTOS] = "Redirect Type of Service and Host";
	if (type == ICMP_SOURCE_QUENCH)
		dprintf(STDOUT_FILENO, "Source Quench");
	else if (type == ICMP_CSRTR_ADV)
		dprintf(STDOUT_FILENO, "Router Advertisement");
	else if (type == ICMP_CSRTR_DSC)
		dprintf(STDOUT_FILENO, "Router Discovery");
	else if (type == ICMP_TIME_EXCEEDED && code == ICMP_EXC_TTL)
		dprintf(STDOUT_FILENO, "Time to live exceeded");
	else if (type == ICMP_TIME_EXCEEDED && code == ICMP_EXC_FRAGTIME)
		dprintf(STDOUT_FILENO, "Frag reassembly time exceeded");
	else if (type == ICMP_TIME_EXCEEDED)
		dprintf(STDOUT_FILENO, "Time exceeded, Unknown Code: %lu", code);
	else if (type == ICMP_REDIRECT && code <= ICMP_REDIR_HOSTTOS && buf[code])
		dprintf(STDOUT_FILENO, buf[code]);
	else if (type == ICMP_REDIRECT)
		dprintf(STDOUT_FILENO, "Redirect, Unknown Code: %lu", code);
}

static void	print_nonecho(t_ping *ft_ping, t_headers *headers)
{
	size_t			type;
	size_t			code;

	type = ft_ping->in.recv.hdrs.icmp->type;
	code = ft_ping->in.recv.hdrs.icmp->code;
	if (!type || type == ICMP_ECHO)
		return ;
	dprintf(STDOUT_FILENO, "%lu bytes from %s: ",
		ft_ping->in.recv.hdrs.datalen + sizeof(t_icmp),
		inet_ntoa(ft_ping->in.recv.peer_addr.sin_addr));
	if (type != ICMP_DEST_UNREACH && type != ICMP_SOURCE_QUENCH
		&& type != ICMP_PARAMETERPROB && type != ICMP_TIME_EXCEEDED
		&& type != ICMP_REDIRECT && type != ICMP_CSRTR_ADV
		&& type != ICMP_CSRTR_DSC)
		dprintf(STDOUT_FILENO, "Bad ICMP type: %lu", type);
	else if (type == ICMP_DEST_UNREACH)
		print_unreach(code);
	else if (type == ICMP_PARAMETERPROB)
		dprintf(STDOUT_FILENO, "Parameter probe: IP address = %s",
			inet_ntoa(*(t_inaddr *)&(ft_ping->in.recv.hdrs.icmp->un.gateway)));
	else
		print_common(type, code);
	dprintf(STDOUT_FILENO, "\n");
	print_headers(ft_ping, headers);
}

/*
** if it is not an echo reply we've received, we will check if it is ours and 
** then call the print function 
*/
void	icmp_noecho(t_ping *ft_ping)
{
	t_headers	hdrs;

	if (ft_ping->in.recv.hdrs.datalen < sizeof(t_ip) + sizeof(t_icmp))
		return ;
	hdrs.ip = (t_ip *)ft_ping->in.recv.hdrs.data;
	if (ft_ping->in.recv.hdrs.datalen < sizeof(t_ip) + 64)
		return ;
	hdrs.datalen = ft_ping->in.recv.hdrs.datalen
		- (hdrs.ip->ihl * 4) - sizeof(t_icmp);
	if (hdrs.datalen > ft_ping->in.recv.hdrs.datalen)
		return ;
	hdrs.icmp = (t_icmp *)(((char *)hdrs.ip) + (hdrs.ip->ihl * 4));
	hdrs.data = ((char *)(hdrs.icmp)) + sizeof(t_icmp);
	if (ft_ping->out.daddr.sin_addr.s_addr != hdrs.ip->daddr)
		return ;
	if ((hdrs.icmp->un.echo.id) != htons(ft_ping->pid))
		return ;
	if (hdrs.ip->protocol != IPPROTO_ICMP
		|| hdrs.icmp->type != ICMP_ECHO)
		return ;
	ft_ping->in.count.err++;
	print_nonecho(ft_ping, &hdrs);
}
