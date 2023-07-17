/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:17:04 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/17 09:12:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ping(t_ping *ft_ping)
{

	t_time	start;
	t_time	timeout = {1,0};
	gettimeofday(&start, NULL);
	while (1)
	{
		ping_in(ft_ping);
		if (timed_out(start, timeout))
		{
			printf("T\n");
			ping_out(ft_ping);
			gettimeofday(&start, NULL);
		}
		usleep(200);
	}     
}
