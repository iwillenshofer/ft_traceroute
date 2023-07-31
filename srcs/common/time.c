/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:12:12 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/31 14:40:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** returns a timeval with the difference between begin and end.
*/
static t_time	elapsed_time(t_time begin, t_time end)
{
	int		nsec;
	t_time	diff;

	if (end.tv_usec < begin.tv_usec)
	{
		nsec = (begin.tv_usec - end.tv_usec) / 1000000 + 1;
		begin.tv_usec -= 1000000 * nsec;
		begin.tv_sec += nsec;
	}
	if (end.tv_usec - begin.tv_usec > 1000000)
	{
		nsec = (end.tv_usec - begin.tv_usec) / 1000000;
		begin.tv_usec += 1000000 * nsec;
		begin.tv_sec -= nsec;
	}
	diff.tv_sec = end.tv_sec - begin.tv_sec;
	diff.tv_usec = end.tv_usec - begin.tv_usec;
	return (diff);
}

/*
** returns the elapsed time in ms, up to (INT_MAX) ms,
** which would result in 2147483 secs, or 35791 minutes or 596
** hours before overflowing.
** Overflow will not be handled.
*/
double	elapsed_time_ms(t_time begin, t_time end)
{
	t_time	elapsed;

	elapsed = elapsed_time(begin, end);
	return ((double)elapsed.tv_sec * 1000 + (double)elapsed.tv_usec / 1000);
}

/*
** returns whether the elapsed time between begin and now
** is greater than timeout
*/
t_bool	timed_out(t_time begin, t_time timeout)
{
	t_time	now;
	t_time	elapsed;

	gettimeofday(&now, NULL);
	elapsed = elapsed_time(begin, now);
	if (elapsed.tv_sec > timeout.tv_sec)
		return (true);
	else if (elapsed.tv_sec < timeout.tv_sec)
		return (false);
	else if (elapsed.tv_usec >= timeout.tv_usec)
		return (true);
	return (false);
}
