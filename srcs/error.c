/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:57:40 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 23:16:27 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void fatal(t_ping *ft_ping, char *msg, t_bool usage)
{
	if (msg)
		fprintf(stderr, "%s\n", msg);
	if (usage == true)
		print_shortusage(ft_ping);
	//free gracefully whatever we preallocated in ft_ping.
	exit(2);
}
