/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 23:28:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_ERRORS_H
# define FT_PING_ERRORS_H

# include "ft_ping_types.h"

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

char *get_errorstr(t_ping *ft_ping, char *error, char *arg1, char *arg2);
void print_error(char *error, char *arg1, char *arg2);
void fatal(t_ping *ft_ping, char *msg, t_bool usage);
void prs_fatal(t_ping *ft_ping, const char *error, const char *s, t_bool shortusage);

#endif
