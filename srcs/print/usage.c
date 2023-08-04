/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:08:03 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/01 10:39:37 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	prt_options(t_trace *tr, int kind, int used, int preceeding)
{
	size_t		i;
	t_lstopt	*opt;

	i = 0;
	opt = tr->opts.available;
	if (kind == OPTT_NULL)
		used += dprintf(STDERR_FILENO, "%s", " -");
	while (i < OPT_LSTSIZE)
	{
		if (used >= 70)
			used = dprintf(STDERR_FILENO, "\n%*s", preceeding, "") - 1;
		if (kind == OPRT_SHORTCUT && opt[i].type == OPTT_NULL)
			used += dprintf(STDERR_FILENO, "%c", opt[i].shortcut);
		else if (kind == OPRT_DSHORTCUT && opt[i].type != OPTT_NULL)
			used += dprintf(STDERR_FILENO, " [-%c %s]",
					opt[i].shortcut, tname(opt[i].type));
		else if (kind == OPRT_FULLNAME && opt[i].type == OPTT_NULL)
			used += dprintf(STDERR_FILENO, " [--%s]", opt[i].fullname);
		else if (kind == OPRT_DFULLNAME && opt[i].type != OPTT_NULL)
			used += dprintf(STDERR_FILENO, " [--%s=%s]",
					opt[i].fullname, tname(opt[i].type));
		i++;
	}
	return (used);
}

char	*tname(int type)
{
	if (type == OPTT_FTTL)
		return (OSTR_FTTL);
	else if (type == OPTT_MAXTTL)
		return (OSTR_MAXTTL);
	else if (type == OPTT_SQUERIES)
		return (OSTR_SQUERIES);
	else if (type == OPTT_NQUERIES)
		return (OSTR_NQUERIES);
	else if (type == OPTT_PORT)
		return (OSTR_PORT);
	return (OSTR_NULL);
}

void	print_usage(t_trace *tr)
{
	int			preceeding;
	int			used;

	preceeding = dprintf(STDERR_FILENO, "Usage: %s", tr->program);
	used = preceeding;
	used = prt_options(tr, OPRT_SHORTCUT, used, preceeding);
	used = prt_options(tr, OPRT_DSHORTCUT, used, preceeding);
	used = prt_options(tr, OPRT_FULLNAME, used, preceeding);
	used += prt_options(tr, OPRT_DFULLNAME, used, preceeding);
	dprintf(STDERR_FILENO, " host [ packetlen ]\n");
	exit(0);
}

void	print_shortusage(t_trace *tr)
{
	dprintf(STDERR_FILENO, ERR_SRTUSAGE, tr->program, tr->program);
}
