/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:46:30 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 20:40:07 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** functions to print ICMP errors
** its called when printing the received packets.
*/

static void	print_destunreach(t_icmp *i)
{
	if (i->code == ICMP_UNREACH_NET || i->code == ICMP_UNREACH_NET_UNKNOWN
		|| i->code == ICMP_UNREACH_ISOLATED
		|| i->code == ICMP_UNREACH_TOSNET)
		printf(" !N");
	else if (i->code == ICMP_UNREACH_HOST
		|| i->code == ICMP_UNREACH_HOST_UNKNOWN
		|| i->code == ICMP_UNREACH_TOSHOST)
		printf(" !H");
	else if (i->code == ICMP_UNREACH_NET_PROHIB
		|| i->code == ICMP_UNREACH_HOST_PROHIB
		|| i->code == ICMP_UNREACH_FILTER_PROHIB)
		printf(" !X");
	else if (i->code == ICMP_UNREACH_PROTOCOL)
		printf(" !P");
	else if (i->code == ICMP_UNREACH_NEEDFRAG)
		printf(" !F-%d", ntohs(i->un.frag.mtu));
	else if (i->code == ICMP_UNREACH_SRCFAIL)
		printf(" !S");
	else if (i->code == ICMP_UNREACH_HOST_PRECEDENCE)
		printf(" !V");
	else if (i->code == ICMP_UNREACH_PRECEDENCE_CUTOFF)
		printf(" !C");
	else
		printf(" !<%u>", i->code);
}

/*
** print an error if the icmp is not TTL exceeded or Unreacheable PORT.
*/
void	print_icmperror(t_icmp *i)
{
	if (i->type == ICMP_TIME_EXCEEDED
		|| (i->type == ICMP_DEST_UNREACH && i->code == ICMP_UNREACH_PORT))
		return ;
	if (i->type == ICMP_DEST_UNREACH)
		print_destunreach(i);
	else
		printf(" !<%u-%u>", i->type, i->code);
}
