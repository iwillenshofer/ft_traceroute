/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:41:39 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 21:23:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	parse_value_count(t_ping *ft_ping, size_t value)
{
	ft_ping->options.all.count = value;
}

void	parse_value_interval(t_ping *ft_ping, size_t value)
{
	ft_ping->options.all.count = value;
}

void	parse_value_size(t_ping *ft_ping, size_t value, char *original)
{
	if (value > 65399)
		parse_fatal(ft_ping, ERR_PARSE_TOOBIG, original, NULL);
	ft_ping->options.echo.size = value;
}

void	parse_value_preload(t_ping *ft_ping, size_t value, char *original)
{
	if (value > INT_MAX)
		parse_fatal(ft_ping, ERR_PARSE_PRELOAD, original, NULL);
	ft_ping->options.echo.size = value;

}
