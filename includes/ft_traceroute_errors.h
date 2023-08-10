/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 07:31:53 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_ERRORS_H
# define FT_TRACEROUTE_ERRORS_H

# include "ft_traceroute_types.h"

# define ERR_BUF 128

# define ERR_FIRSTHOP "%s: first hop out of range `%s'\n"
# define ERR_MAXHOP "%s: invalid hops value `%s'\n"
# define ERR_PORT "%s: invalid port number `%s'\n"
# define ERR_WAIT "%s: ridiculous waiting time `%s'\n"
# define ERR_TRIES "%s: number of tries should be between 1 and 10\n"
# define ERR_INVALIDOPT "%s: invalid option -- '%s'\n"
# define ERR_MISSING_HOST "%s: missing host operand\n"
# define ERR_UNKNOWN_HOST "%s: unknown host\n"
# define ERR_INVALID "%s: invalid value (%s)\n"
# define ERR_SRTUSAGE "Try '%s --help' or '%s --usage' for more information.\n"
# define ERR_LUNRECG_OPT "%s: unrecognized option '--%s'\n"
# define ERR_ALLOWNOARGS "%s: option '--%s' doesn't allow an argument\n"
# define ERR_PREQLVAL "%s: option '--%s' requires an argument\n"
# define ERR_PREQVAL "%s: option requires an argument -- '%s'\n"
# define ERR_EXTRAARG "%s: extra arg '%s'\n"
# define ERR_PACKLENV  "%s: cannot handle \"packetlen\" cmdline arg '%s'\n"
# define ERR_PACKLENS  "%s: too big packetlen %s specified\n"
# define ERR_BIND "bind\n"
# define ERR_SOCKET "socket\n"
# define ERR_REUSEPORT "setsockopt SO_REUSEPORT\n"
# define ERR_TTL "setsockopt IP_TTL\n"
# define ERR_ADDR "%s: %s\n"

void	prs_fatal(t_trace *tr,
			const char *error, const char *s, t_bool shortusage);

#endif
