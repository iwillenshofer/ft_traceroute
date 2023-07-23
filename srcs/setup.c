/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:42:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 12:23:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file sets up the ft_ping structure.
*/

#include "ft_ping.h"

void	set_default_pattern(t_ping *ft_ping)
{
	return ;
	size_t	i;

	i = 0;
	while (i < DFL_CUSTOM_PATTERN_SIZE)
	{
		ft_ping->options.echo.pattern.pattern[i] = i;
		i++;
	}
	ft_ping->options.echo.pattern.size = DFL_CUSTOM_PATTERN_SIZE;
}

void	set_defaults(t_ping *ft_ping)
{
	ft_ping->options.echo.size = DFL_PACKET_SIZE;
	ft_ping->options.all.ttl = DFL_TTL;
	set_default_pattern(ft_ping);
}

void	setup(t_ping *ft_ping, char **argv)
{
	ft_bzero(ft_ping, sizeof(t_ping));
	set_defaults(ft_ping);
	parse(ft_ping, argv);
	/*
	** initial options that should be parsed.
	*/
	ft_ping->options.all.ttl = 3;
	ft_ping->options.all.count = 10;



	ft_ping->pid = getpid();
}
