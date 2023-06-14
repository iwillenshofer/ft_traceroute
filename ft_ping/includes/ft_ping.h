/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:41:35 by iwillens          #+#    #+#             */
/*   Updated: 2023/06/14 09:44:57 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <sys/socket.h>

# if __APPLE__
#  include "ft_ping_mac.h"
# else
#  include "ft_ping_linux.h"
# endif



# define THISISAMAC 0

# if __APPLE__
#  undef THISISAMAC
#  define THISISAMAC 1
# endif



#endif
