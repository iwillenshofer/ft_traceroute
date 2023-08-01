/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/31 14:54:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_ERRORS_H
# define FT_TRACEROUTE_ERRORS_H

# include "ft_traceroute_types.h"

# define ERR_BUF 128

# define ERR_INVALIDOPT "%s: invalid option -- '%s'\n"
# define ERR_UNKNOWN_HOST "%s: unknown host\n"
# define ERR_PVALUE "%s: invalid value (%s)\n"
# define ERR_PREQVAL "%s: option requires an argument -- '%s'\n"
# define ERR_PREQLVAL "%s: ping: option '--%s' requires an argument\n"
# define ERR_PPATTERN "%s: error in pattern near %s\n"
# define ERR_PPRELOAD "%s: invalid preload value (%s)\n"
# define ERR_PTOOBIG "%s: option value too big: %s\n"
# define ERR_UNRECOGNIZED_OPTION "%s: unrecognized option '%s'\n"
# define ERR_LUNRECG_OPT "%s: unrecognized option '--%s'\n"
# define ERR_SRTUSAGE "Try '%s --help' or '%s --usage' for more information.\n"
# define ERR_MISSING_HOST "%s: missing host operand\n"
# define ERR_ALLOWNOARGS "%s: option '--%s' doesn't allow an argument\n"
# define ERR_VALTOOSMALL "%s: option value too small: %s\n"
# define ERR_INCOMP_INTFLOOD "%s: -f and -i incompatible options\n"
# define ERR_SCKOPTTTL "%s: setsockopt(IP_TTL)\n"
# define ERR_SOCKET "%s: Lacking privilege for icmp socket.\n"
# define ERR_SEND "%s: sending packet"

void	prs_fatal(t_ping *ft_ping,
			const char *error, const char *s, t_bool shortusage);

#endif
