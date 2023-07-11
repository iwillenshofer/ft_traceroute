/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_errors.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:39:25 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/04 15:15:17 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_ERRORS_HPP
# define FT_PING_ERRORS_HPP

# include "ft_ping_types.h"

# define ERROR_UNKNOWN_HOST "%s: unknown host %s"
# define ERROR_INVALID_ARGUMENT "%s: invalid argument %s"
# define ERROR_INVALID_ARGUMENTS "%s: invalid arguments"

char *get_errorstr(t_ping *ft_ping, char *error, char *arg1, char *arg2);
void print_error(char *error, char *arg1, char *arg2);
void fatal(t_ping *ft_ping, char *msg, t_bool usage);

#endif