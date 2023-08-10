/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:42:28 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 22:43:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	prs_fatal(t_trace *tr, const char *error,
	const char *s, t_bool shortusage)
{
	dprintf(STDERR_FILENO, error, s);
	if (shortusage)
		print_shortusage(tr);
	exit (1);
}

void	prs_fatal_pos(t_trace *tr,
			const char *error, char **pos)
{
	dprintf(STDERR_FILENO, error, *pos, pos - tr->argv.argv);
	exit (1);
}
