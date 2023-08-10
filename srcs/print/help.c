/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:43:19 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 19:52:19 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void	print_helpopts(t_lstopt *opt, size_t idx)
{
	char		buf[64];

	ft_strcpy(buf, opt[idx].fullname);
	if (opt[idx].type != OPTT_NULL)
	{
		ft_strcpy(buf + ft_strlen(buf), "=");
		ft_strcpy(buf + ft_strlen(buf), tname(opt[idx].type));
	}
	dprintf(STDOUT_FILENO, "  -%c", opt[idx].shortcut);
	if (opt[idx].type)
		dprintf(STDOUT_FILENO, " %s", tname(opt[idx].type));
	dprintf(STDOUT_FILENO, "  --%-21s", buf);
	if (!opt[idx].type)
		dprintf(STDOUT_FILENO, "\t");
	dprintf(STDOUT_FILENO, "\t");
	dprintf(STDOUT_FILENO, "%s\n", opt[idx].desc);
}

void	print_help(t_trace *tr)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = tr->opts.available;
	print_usage(tr, false);
	dprintf(STDOUT_FILENO, HPL_OPTIONS);
	while (i < OPT_LSTSIZE)
	{
		print_helpopts(opt, i);
		i++;
	}
	dprintf(STDOUT_FILENO, "\nArguments:\n%s\n%s\n", HPL_ARGS, HPL_ARGS2);
	exit(0);
}

void	print_version(t_trace *tr)
{
	dprintf(STDOUT_FILENO, VRS, tr->argv.program, 0, UINT_MAX);
	dprintf(STDOUT_FILENO, VRS1);
	dprintf(STDOUT_FILENO, VRS2);
	dprintf(STDOUT_FILENO, VRS3);
	dprintf(STDOUT_FILENO, VRS4);
	dprintf(STDOUT_FILENO, VRS5);
	exit(0);
}
