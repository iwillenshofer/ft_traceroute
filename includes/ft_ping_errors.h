/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/24 12:52:46 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_ERRORS_H
# define FT_PING_ERRORS_H

# include "ft_ping_types.h"

# define ERROR_UNKNOWN_HOST "%s: unknown host %s"
# define ERROR_INVALID_ARGUMENT "%s: invalid argument %s"
# define ERROR_INVALID_ARGUMENTS "%s: invalid arguments"
# define ERR_PARSE_VALUE "%s: invalid value (`%s' near `%s')\n"
# define ERR_PARSE_PATTERN "%s: error in pattern near %s\n"
# define ERR_PARSE_PRELOAD "%s: invalid preload value (%s)\n"
# define ERR_PARSE_TOOBIG "%s: option value too big: %s\n"
# define ERR_UNRECOGNIZED_OPTION "%s: unrecognized option '%s'\n"

char *get_errorstr(t_ping *ft_ping, char *error, char *arg1, char *arg2);
void print_error(char *error, char *arg1, char *arg2);
void fatal(t_ping *ft_ping, char *msg, t_bool usage);
void parse_fatal(t_ping *ft_ping, char *error, char *s1, char *s2);

#endif