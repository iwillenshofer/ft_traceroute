/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:50:46 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 10:51:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	prs_single(t_ping *ft_ping, char c)
{
	if (c == '?')
		print_help(ft_ping);
	else if (c == 'U')
		print_usage(ft_ping);
}
