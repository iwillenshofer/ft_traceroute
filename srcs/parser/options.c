/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:27:23 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 23:26:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static t_lstopt	new_option(char shortcut, char type, char *name)
{
	t_lstopt	new;

	ft_bzero(&new, sizeof(new));
	new.shortcut = shortcut;
	new.type = type;
	ft_strcpy(new.fullname, name);
	return (new);
}

static void	add_descriptions(t_trace *tr)
{
	t_lstopt	*opt;

	opt = tr->opts.available;
	ft_strcpy(opt[OPT_FIRSTTTL].desc, ODSC_FIRSTTTL);
	ft_strcpy(opt[OPT_MAXTTL].desc, ODSC_MAXTTL);
	ft_strcpy(opt[OPT_PORT].desc, ODSC_PORT);
	ft_strcpy(opt[OPT_SQUERIES].desc, ODSC_SQUERIES);
	ft_strcpy(opt[OPT_RESOLVEH].desc, ODSC_RESOLVEH);
	ft_strcpy(opt[OPT_NQUERIES].desc, ODSC_NQUERIES);
	ft_strcpy(opt[OPT_USAGE].desc, ODSC_USAGE);
	ft_strcpy(opt[OPT_HELP].desc, ODSC_HELP);
	ft_strcpy(opt[OPT_VERSION].desc, ODSC_VERSION);
}

void	add_options(t_trace *tr)
{
	t_lstopt	*opt;

	opt = tr->opts.available;
	opt[OPT_FIRSTTTL] = new_option('f', OPTT_FTTL, "first");
	opt[OPT_MAXTTL] = new_option('m', OPTT_MAXTTL, "max-hops");
	opt[OPT_SQUERIES] = new_option('N', OPTT_SQUERIES, "sim-queries");
	opt[OPT_PORT] = new_option('p', OPTT_PORT, "port");
	opt[OPT_RESOLVEH] = new_option('n', OPTT_NULL, "resolve-hostnames");
	opt[OPT_NQUERIES] = new_option('q', OPTT_NQUERIES, "queries");
	opt[OPT_USAGE] = new_option('u', OPTT_NULL, "usage");
	opt[OPT_HELP] = new_option('?', OPTT_NULL, "help");
	opt[OPT_VERSION] = new_option('V', OPTT_NULL, "version");
	add_descriptions(tr);
	add_handlers(tr);
}

/*
** retrieves an option by fullname.
*/
t_lstopt	*opt_byfullname(t_trace *tr, char *s)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = tr->opts.available;
	while (i < OPT_LSTSIZE)
	{
		if (!(ft_strcmp(opt[i].fullname, s)))
			return (&(opt[i]));
		i++;
	}
	return (NULL);
}

/*
** retrieves an option by shortcut.
*/
t_lstopt	*opt_byshortcut(t_trace *tr, char c)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = tr->opts.available;
	while (i < OPT_LSTSIZE)
	{
		if (opt[i].shortcut == c)
			return (&(opt[i]));
		i++;
	}
	return (NULL);
}
