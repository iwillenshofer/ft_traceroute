/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:41:36 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 23:22:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	parse_value_pattern(t_ping *ft_ping, char *value)
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
		ft_ping->options.echo.pattern.pattern[size/2] = c;
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

void	parse_value_ttl(t_ping *ft_ping, size_t value, char *original)
{
	if (value > 255)
		parse_fatal(ft_ping, ERR_PARSE_TOOBIG, original, NULL);
}

void	parse_value_timeout(t_ping *ft_ping, size_t value, char *original)
{
	if (value > INT_MAX)
		parse_fatal(ft_ping, ERR_PARSE_TOOBIG, original, NULL);
}
