/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 20:34:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_ERRORS_H
# define FT_TRACEROUTE_ERRORS_H

# include "ft_traceroute_types.h"

# define ERR_BUF 128

# define ERR_FIRSTHOP "first hop out of range\n"
# define ERR_MAXHOP "invalid hops value `%s'\n"
# define ERR_PORT "invalid port number `%s'\n"
# define ERR_WAIT "ridiculous waiting time `%s'\n"
# define ERR_TRIES "number of tries should be between 1 and 10\n"
# define ERR_MISSING_HOST "missing host operand\n"
# define ERR_UNKNOWN_HOST "unknown host\n"
# define ERR_INVALID "invalid value (%s)\n"
# define ERR_SRTUSAGE "Try '%s --help' or '%s --usage' for more information.\n"
# define ERR_ALLOWNOARGS "option '--%s' doesn't allow an argument\n"
# define ERR_PREQLVAL "option '--%s' requires an argument\n"
# define ERR_PREQVAL "option requires an argument -- '%s'\n"
# define ERR_PACKLENS  "too big packetlen %s specified\n"
# define ERR_BIND "bind\n"
# define ERR_SOCKET "socket\n"
# define ERR_REUSEPORT "setsockopt SO_REUSEPORT\n"
# define ERR_TTL "setsockopt IP_TTL\n"
# define ERR_HOST "Cannot handle \"host\" cmdline arg `%s' on \
position 1 (argc %d)\n"
# define ERR_PACKLENV "Cannot handle \"packetlen\" cmdline arg `%s' on \
position 2 (argc %d)\n"
# define ERR_EXTRAARG "Extra arg `%s' (position 3, argc %d)\n"
# define ERR_INVALIDOPT "Bad option `%s' (argc %d)\n"
# define ERR_ADDR "%s: %s\n"

void	prs_fatal(t_trace *tr,
			const char *error, const char *s, t_bool shortusage);

void	prs_fatal_pos(t_trace *tr,
			const char *error, char **pos);

#endif
