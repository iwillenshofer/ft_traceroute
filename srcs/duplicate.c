/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:59:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/18 15:16:35 by iwillens         ###   ########.fr       */
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

void	set_duptrack(t_ping *ft_ping, size_t seq)
{
	char	*c;
	char	*next;
	size_t	pos;

	pos = seq % (MAX_SEQ_TRACK * 8);
	if(!seq)
		ft_bzero(ft_ping->in.track, sizeof(ft_ping->in.track));
	c = &(ft_ping->in.track[pos / 8]);
	next = c + 1;
	if (next >= ft_ping->in.track + sizeof(ft_ping->in.track))
		next = ft_ping->in.track;
	*next = 0;
	*c = *c + (1 << pos % 8);
}

t_bool	check_duptrack(t_ping *ft_ping, size_t seq)
{
	char	*c;
	size_t	pos;

	pos = seq % (MAX_SEQ_TRACK * 8);
	c = &(ft_ping->in.track[pos / 8]);
	return (*c & (1 << pos % 8));
}
