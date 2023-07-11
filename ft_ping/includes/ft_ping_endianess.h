/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_endianess.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:46:44 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/11 10:59:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_ENDIANESS_H
# define FT_PING_ENDIANESS_H

# include "ft_ping_types.h"

t_bool		host_is_littleendian(void);
void		hostbyteorder(void *value, size_t datasize);
void		networkbyteorder(void *value, size_t datasize);
t_u8bits	invert_bitfield8(t_u8bits hostshort);
t_u16bits	invert_bytes16(t_u16bits hostshort);
t_u32bits	invert_bytes32(t_u32bits hostlong);

#endif
