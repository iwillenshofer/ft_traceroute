/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_parse.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:00:10 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/26 12:37:11 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_PARSE_H
# define FT_TRACEROUTE_PARSE_H

/*
** list of options allowed by this program.
** OPT_LSTSIZE must be the count of options available
*/
# define OPT_COUNT			0
# define OPT_INTERVAL		1
# define OPT_NUMERIC		2
# define OPT_TTL			3
# define OPT_VERBOSE		4
# define OPT_TIMEOUT		5
# define OPT_FLOOD			6
# define OPT_PRELOAD		7
# define OPT_PATTERN		8
# define OPT_QUIET			9
# define OPT_SIZE			10
# define OPT_HELP			11
# define OPT_USAGE			12
# define OPT_VERSION		13
# define OPT_LSTSIZE		14

/*
** Descriptions for the above otions
*/
# define ODSC_COUNT		"stop after sending NUMBER packets"
# define ODSC_INTERVAL	"wait NUMBER seconds between sending each packet"
# define ODSC_NUMERIC	"do not resolve host addresses"
# define ODSC_TTL		"specify N as time-to-live"
# define ODSC_VERBOSE	"verbose output"
# define ODSC_TIMEOUT	"stop after N seconds"
# define ODSC_FLOOD		"flood ping"
# define ODSC_PRELOAD	"send NUMBER packets as fast as possible before \
falling into normal mode of behavior"
# define ODSC_PATTERN	"fill ICMP packet with given pattern"
# define ODSC_QUIET		"quiet output"
# define ODSC_SIZE		"send NUMBER data octets"
# define ODSC_HELP		"give this help list"
# define ODSC_USAGE		"give a short usage message"
# define ODSC_VERSION	"print program version"

/*
** definitions for option types
** and its printing counterparts
OPTT_NULL: --numeric
OPTT_SHORT: --ttl=N
OPTT_LONG: --count=NUMBER
OPTT_PATTERN: --pattern=PATTERN
*/
# define OPTT_NULL		0
# define OPTT_SHORT		1
# define OPTT_LONG		2
# define OPTT_PATTERN	3

# define OSTR_NULL		""
# define OSTR_SHORT		"N"
# define OSTR_LONG		"NUMBER"
# define OSTR_PATTERN	"PATTERN"

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
# define HPL_USAGE "Usage: %s [OPTION...] HOST ...\n"
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
# define VRS5 "\n\n\033[37;1m      * * *   ft_ping   * * *\033[0m\n\n"

#endif
