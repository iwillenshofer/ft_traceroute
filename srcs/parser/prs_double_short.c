/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_double_short.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:41:36 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 11:29:13 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** parses an hex pattern into ft_ping->options.echo.pattern.pattern
*/
void	prs_value_pattern(t_ping *ft_ping, char *value)
{
	size_t	size;
	char	c;

	size = 0;
	c = 0;
	while (value && *value && size < MAX_PATTERN)
	{
		if (*value >= '0' && *value <= '9')
			*value = *value - '0';
		else
			*value = (*value - 'a') + 10;
		if ((size % 2))
			c = c << 4;
		c += *value;
		ft_ping->options.echo.pattern.pattern[size / 2] = c;
		if ((size % 2))
			c = 0;
		size++;
		value++;
	}
	if (size % 2 || !size)
		size = size / 2 + 1;
	else
		size = size / 2;
	ft_ping->options.echo.pattern.size = size;
}

void	prs_value_ttl(t_ping *ft_ping, size_t value, char *original)
{
	if (value > 255)
		prs_fatal(ft_ping, ERR_PTOOBIG, original, false);
	ft_ping->options.all.ttl = value;
}

void	prs_value_timeout(t_ping *ft_ping, size_t value, char *original)
{
	if (value > INT_MAX)
		prs_fatal(ft_ping, ERR_PTOOBIG, original, false);
	ft_ping->options.all.timeout = value;
}
