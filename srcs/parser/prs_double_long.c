/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_double_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:41:39 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 11:29:13 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	prs_value_count(t_ping *ft_ping, size_t value)
{
	ft_ping->options.all.count = value;
}

void	prs_value_interval(t_ping *ft_ping, size_t value)
{
	ft_ping->options.all.count = value;
}

void	prs_value_size(t_ping *ft_ping, size_t value, char *original)
{
	if (value > 65399)
		prs_fatal(ft_ping, ERR_PTOOBIG, original, false);
	ft_ping->options.echo.size = value;
}

void	prs_value_preload(t_ping *ft_ping, size_t value, char *original)
{
	if (value > INT_MAX)
		prs_fatal(ft_ping, ERR_PPRELOAD, original, false);
	ft_ping->options.echo.size = value;
}
