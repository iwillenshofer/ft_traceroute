/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:08:03 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/04 15:19:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** those are all printable options available in the real ping program for
** debian wheezie. More may be added to our program.
**  [-LRUbdfnqrvVaAD] [-c count] [-i interval] [-w deadline]
**             [-p pattern] [-s packetsize] [-t ttl] [-I interface]
**             [-M pmtudisc-hint] [-m mark] [-S sndbuf]
**             [-T tstamp-options] [-Q tos] [hop1 ...] destination
** being in the *options[] list does not mean it is implemented/available.
** Available options for our implementation is defined in OPTS_SINGLE and
**  OPTS_DOUBLE definitions, both for the main and bonus releases.
** See ft_ping_bonus.h and ft_ping.h
*/

char const	*printable_option(char c)
{
	char const			**head;
	static const char	*options[] = {
		"[-c count]", "[-i interval]", "[-I interface]", "[-m mark]",
		"[-M pmtudisc_option]", "[-l preload]", "[-p pattern]", "[-Q tos]",
		"[-s packetsize]", "[-S sndbuf]", "[-t ttl]", "[-T timestamp_option]",
		"[-w deadline]", "[-W timeout]", NULL
	};

	head = options;
	while (*head)
	{
		if ((*head)[2] == c)
			return (*head);
		head++;
	}
	return (NULL);
}

void	print_usage(t_ping *ft_ping)
{
	int			preceeding;
	int			used;
	char		*opts;
	char const	*printable;

	preceeding = fprintf(stderr, "Usage: %s", ft_ping->program);
	used = preceeding + fprintf(stderr, " [-%s]", OPTS_SINGLE);
	(void)used;
	opts = OPTS_DOUBLE;
	while (*opts)
	{
		printable = printable_option(*opts);
		if (printable && used >= 70)
		{
			fprintf(stderr, "\n%*s", preceeding, "");
			used = preceeding;
		}
		if (printable)
			used += fprintf(stderr, " %s", printable);
		opts++;
	}
	fprintf(stderr, " destination\n");
}
