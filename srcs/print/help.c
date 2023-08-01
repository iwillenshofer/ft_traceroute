/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:43:19 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_help(t_ping *ft_ping)
{
	t_lstopt	*opt;
	size_t		i;
	char		buf[64];

	i = 0;
	opt = ft_ping->opts.available;
	dprintf(STDOUT_FILENO, HPL_USAGE, ft_ping->program);
	dprintf(STDOUT_FILENO, HPL_GOAL);
	dprintf(STDOUT_FILENO, HPL_OPTIONS);
	while (i < OPT_LSTSIZE)
	{
		ft_strcpy(buf, opt[i].fullname);
		if (opt[i].type != OPTT_NULL)
		{
			ft_strcpy(buf + ft_strlen(buf), "=");
			ft_strcpy(buf + ft_strlen(buf), tname(opt[i].type));
		}
		dprintf(STDOUT_FILENO, "  -%c, --%-21s %s\n",
			opt[i].shortcut, buf, opt[i].desc);
		i++;
	}
	dprintf(STDOUT_FILENO, "\n%s %s\n", HPL_ARGS, HPL_ARGS2);
	exit(0);
}

void	print_version(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, VRS, ft_ping->program, 0, UINT_MAX);
	dprintf(STDOUT_FILENO, VRS1);
	dprintf(STDOUT_FILENO, VRS2);
	dprintf(STDOUT_FILENO, VRS3);
	dprintf(STDOUT_FILENO, VRS4);
	dprintf(STDOUT_FILENO, VRS5);
	exit(0);
}
