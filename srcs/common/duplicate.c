/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:59:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 23:16:51 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** this file contains functions for tracking duplicated received messages
**  (ft_ping->in.track[MAX_SEQ_TRACK]).
**  Received package sequence numbers are stored bit wise, as a multiple of
**  MAX_SEQ_TRACK * 8bits (defaults to 128 * 8bits).
** If divisor is zero, when setting the track, bzeros the whole array to
**  start over.
*/

void	clear_duptrack(t_ping *ft_ping, size_t seq)
{
	char	*c;
	size_t	pos;
	char	mask;

	pos = seq % (MAX_SEQ_TRACK * 8);
	c = &(ft_ping->in.track[pos / 8]);
	mask = 0xff ^ (1 << (pos % 8));
	*c = *c & mask;
}

void	set_duptrack(t_ping *ft_ping, size_t seq)
{
	char	*c;
	size_t	pos;

	pos = seq % (MAX_SEQ_TRACK * 8);
	c = &(ft_ping->in.track[pos / 8]);
	*c = *c | (1 << (pos % 8));
}

t_bool	check_duptrack(t_ping *ft_ping, size_t seq)
{
	char	*c;
	size_t	pos;

	pos = seq % (MAX_SEQ_TRACK * 8);
	c = &(ft_ping->in.track[pos / 8]);
	return (*c & (1 << pos % 8));
}
