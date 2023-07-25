/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:57:40 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 08:53:50 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char *get_errorstr(t_ping *ft_ping, char *error, char *arg1, char *arg2)
{
	if (arg1 && arg2)
		sprintf((ft_ping->error), error, arg1, arg2);
	else if (arg1)
		sprintf((ft_ping->error), error, arg1);
	else
		sprintf((ft_ping->error), error);
	return(ft_ping->error);
}

void fatal(t_ping *ft_ping, char *msg, t_bool usage)
{
	if (msg)
		fprintf(stderr, "%s\n", msg);
	if (usage == true)
		print_shortusage(ft_ping);
	//free gracefully whatever we preallocated in ft_ping.
	exit(2);
}
