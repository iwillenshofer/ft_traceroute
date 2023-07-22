/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:07:32 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/12 10:42:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_BONUS_H
# define FT_PING_BONUS_H

# include "ft_ping.h"

/*
** mandatory: -h -v
** bonus flags we may want to implement
-f 						# flood ping
-n 						# no idea yet
-m mark
-l preload
-I interface
-M pmtudisc_option
-w deadline
-W timeout
-p pattern
-Q tos
-S sndbuf
-t ttl
-T timestamp_option
-c count 				#NOT ON subject
-i interval 			#NOT ON subject

*/

# ifdef OPTS_SINGLE
#  undef OPTS_SINGLE
# endif
#  define OPTS_SINGLE "hvf"

# ifdef OPTS_DOUBLE
#  undef OPTS_DOUBLE
# endif
#  define OPTS_DOUBLE "mlIMwWpQstTci"

int reverse_lookup(void);

#endif
