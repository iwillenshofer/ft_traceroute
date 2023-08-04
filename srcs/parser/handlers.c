/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:13:29 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/02 19:48:10 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** here are handled all options that need an argument
** f --first-hop (1-30)
** m --max-hop (1-255)
** p --port (1-65536, but if too high, sendto will throw an error)
** w --wait (0 - 60)
** q --tries (1 - 10)
*/
static void	hndlr_doubleopt(t_trace *tr, t_lstopt *opt, char *value)
{
	size_t	val;
	char	errbuf[ERR_BUF + 1];

	snprintf(errbuf, ERR_BUF, "`%s' near `%s'", value, ft_notnumeric(value));
	val = ft_atoul(value);
	if (opt->shortcut == 'f' && (ft_notnumeric(value) || val < 1 || val > DFL_MAXTTL))
		prs_fatal(tr, ERR_FIRSTHOP, value, false);
	else if (opt->shortcut == 'm' && (ft_notnumeric(value) || val < 1 || val > MAX_HOPS))
		prs_fatal(tr, ERR_MAXHOP, value, false);
	else if (opt->shortcut == 'N' && (ft_notnumeric(value)))
		prs_fatal(tr, ERR_INVALID, errbuf, false);
	else if (opt->shortcut == 'p' && (ft_notnumeric(value) || val < 1 || val > MAX_PORT))
		prs_fatal(tr, ERR_PORT, value, false);
	else if (opt->shortcut == 'q' && (ft_notnumeric(value)))
		prs_fatal(tr, ERR_INVALID, errbuf, false);
	else if (opt->shortcut == 'q' && (val < 1 || val > 10))
		prs_fatal(tr, ERR_TRIES, value, false);



/* WILL DO VALUE LIMITING LATER*/
//	if ((opt->shortcut == 'T' && val > 255)
//		|| (opt->shortcut == 'w' && val > INT_MAX)
//		|| (opt->shortcut == 's' && val > MAX_PACKET_SIZE))
//		prs_fatal(tr, ERR_PTOOBIG, value, false);
//	else if (opt->shortcut == 'l' && val > INT_MAX)
//		prs_fatal(tr, ERR_PPRELOAD, value, false);
//	else if (val == 0 && (opt->shortcut == 'T' || opt->shortcut == 'w'))
//		prs_fatal(tr, ERR_VALTOOSMALL, value, false);
	if (opt->shortcut == 'f')
		tr->opts.firsthop = val;
	else if (opt->shortcut == 'm')
		tr->opts.maxhop = val;
	else if (opt->shortcut == 'N')
	{
		if (!val)
			val++;
		tr->opts.squeries = val;
	}
	else if (opt->shortcut == 'p')
		tr->opts.port = val;
	else if (opt->shortcut == 'q')
		tr->opts.nqueries = val;
}

/*
** here are handled all options that do not need an argument
** ? --help
** m --resolve-names
** u --usage
** V --version   
*/
static void	hndlr_singleopt(t_trace *tr, t_lstopt *opt, char *value)
{
	(void)(value);
	if (opt->shortcut == '?')
		print_help(tr);
	if (opt->shortcut == 'u')
		print_usage(tr);
	if (opt->shortcut == 'V')
		print_version(tr);
	if (opt->shortcut == 'n')
		tr->opts.resolvehosts = true;
}

/*
** add the option handlers, so the parser can call
** the apropriate function.
*/
void	add_handlers(t_trace *tr)
{
	t_lstopt	*opt;

	opt = tr->opts.available;
	opt[OPT_RESOLVEH].handler = hndlr_singleopt;
	opt[OPT_HELP].handler = hndlr_singleopt;
	opt[OPT_USAGE].handler = hndlr_singleopt;
	opt[OPT_VERSION].handler = hndlr_singleopt;
	opt[OPT_FIRSTTTL].handler = hndlr_doubleopt;
	opt[OPT_MAXTTL].handler = hndlr_doubleopt;
	opt[OPT_PORT].handler = hndlr_doubleopt;
	opt[OPT_NQUERIES].handler = hndlr_doubleopt;
	opt[OPT_SQUERIES].handler = hndlr_doubleopt;
}
