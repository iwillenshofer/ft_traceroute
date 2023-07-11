/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:47:17 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/10 17:49:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool host_is_littleendian(void)
{
	short i;

	i = 1;
	if (*(char*)(&i))
		return (true);
	return (false);
}
