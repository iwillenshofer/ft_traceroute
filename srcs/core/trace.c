/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:42:54 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 21:27:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** this is the main function...
** strategy:
** we'll use a custom timeout and set reading operation to DONT WAIT instead
**  of a select()
** 1. will sent a bunch of packets (16 by default)
** 2. will always listen
** 3. will try to print result, checking if it is marked as received
**  (until timeout);
**  - if result is not received and timeout is expired, just print '*' and
**   set it as received.
** 4. will send further packets as we receive previous ones
**  (either from real receipt or by timeout)
*/
void	traceroute(t_trace *tr)
{
	while (!(tr->done))
	{
		sendpackets(tr);
		recvpackets(tr);
		prntpackets(tr);
		usleep(DFL_SLEEP);
	}
}
