/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:00:10 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 21:22:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_PARSE_H
# define FT_TRACEROUTE_PARSE_H

/*
**  
**  -f first_ttl  --first=first_ttl
**    Start from the first_ttl hop (instead from 1)
**  -m max_ttl  --max-hops=max_ttl
**    Set the max number of hops (max TTL to be reached). Default is 30
**  -N squeries  --sim-queries=squeries
**   Set the number of probes to be tried simultaneously (default is 16)
**  -p port  --port=port  Set the destination port to use. It is either
**                        initial udp port value for "default" method
**                        (incremented by each probe, default is 33434), or
**                        initial seq for "icmp" (incremented as well,
**                        default from 1), or some constant destination
**                        port for other methods (with default of 80 for
**                        "tcp", 53 for "udp", etc.)
**  -q nqueries  --queries=nqueries
**    Set the number of probes per each hop. Default is 3
**  -n                    Do not resolve IP addresses to their domain names
**  -V  --version         Print version info and exit
**  --help                Read this help and exit
*/

/*
** list of options allowed by this program.
** OPT_LSTSIZE must be the count of options available
*/
# define OPT_FIRSTTTL		0
# define OPT_MAXTTL			1
# define OPT_PORT			2
# define OPT_SQUERIES		3
# define OPT_NQUERIES		4
# define OPT_RESOLVEH		5
# define OPT_USAGE			6
# define OPT_HELP			7
# define OPT_VERSION		8
# define OPT_LSTSIZE		9

/*
** Descriptions for the above otions
*/

# define ODSC_FIRSTTTL	"Start from the first_ttl hop (instead from 1)"
# define ODSC_MAXTTL	"Set the max number of hops \
(max TTL to be reached). Default is 30"
# define ODSC_PORT		"Set the initial value for destination port. \
(default: 33434)"
# define ODSC_SQUERIES	"Set the number of probes to be tried simultaneously \
(default is 16)"
# define ODSC_NQUERIES	"Set the number of probes per each hop. Default is 3"
# define ODSC_RESOLVEH	"Do not resolve IP addresses to their domain names"
# define ODSC_USAGE		"give a short usage message and exit"
# define ODSC_HELP		"Read this help and exit"
# define ODSC_VERSION	"Print version info and exit"

# define OPTT_NULL		0
# define OPTT_FTTL		1
# define OPTT_MAXTTL	2
# define OPTT_SQUERIES	3
# define OPTT_NQUERIES	4
# define OPTT_PORT		5

# define OSTR_NULL		""
# define OSTR_FTTL		"first_ttl"
# define OSTR_MAXTTL	"max_ttl"
# define OSTR_SQUERIES	"squeries"
# define OSTR_NQUERIES	"nqueries"
# define OSTR_PORT		"port"

# define OSTR_QUERIES	"nqueries"

/*
** definitions types for printing.
** examples:
** OPRT_SHORTCUT: -?
** OPRT_SHORTCUT: -c NUMBER
** OPRT_FULLNAME: --help
** OPRT_DFULLNAME: --count NUMBER
*/
# define OPRT_SHORTCUT		0
# define OPRT_DSHORTCUT		1
# define OPRT_FULLNAME		2
# define OPRT_DFULLNAME		3

/*
** Definitions for Help strings
*/
# define HPL_USAGE "Usage: %s [OPTION...] host [ packetlen ]\n"
# define HPL_GOAL "Send ICMP ECHO_REQUEST packets to network hosts.\n\n"
# define HPL_OPTIONS "Options valid for all request types:\n\n"
# define HPL_ARGS "Mandatory or optional arguments to long options are also"
# define HPL_ARGS2 "mandatory or optional for any corresponding short options."

/*
** Definitions for Version Strings
*/
# define VRS "\033[37;1m%s Version %u.%u\033[0m\n"
# define VRS1 "\033[0m\033[38;2;123;145;255m _         _  _  _\n"
# define VRS2 "\033[38;2;87;115;255m<_> _ _ _ <_>| || | ___ ._ _  ___\n"
# define VRS3 "\033[38;2;207;59;255m| || | | || || || |/ ._>| ' |<_-<\n"
# define VRS4 "\033[38;2;255;135;255m|_||__/_/ |_||_||_|\\___.|_|_|/__/\033[0m"
# define VRS5 "\n\n\033[37;1m  * * *   ft_traceroute   * * *\033[0m\n\n"

#endif
