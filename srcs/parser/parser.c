/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/08/02 19:49:46 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	prs_fatal(t_trace *tr, const char *error,
	const char *s, t_bool shortusage)
{
	dprintf(STDERR_FILENO, error, tr->program, s);
	if (shortusage)
		print_shortusage(tr);
	exit (1);
}

static char	**prs_shortname(t_trace *tr, char **argv)
{
	char		*c;
	t_lstopt	*opt;
	char		err[2];

	err[1] = 0;
	c = (*argv) + 1;
	while (*c)
	{
		err[0] = *c;
		opt = opt_byshortcut(tr, *c);
		if (!opt)
			prs_fatal(tr, ERR_INVALIDOPT, err, true);
		if (opt->type == OPTT_NULL)
			opt->handler(tr, opt, NULL);
		else if (*(++c))
			opt->handler(tr, opt, c);
		else if (!(*(++argv)))
			prs_fatal(tr, ERR_PREQVAL, err, true);
		else
			opt->handler(tr, opt, *(argv));
		if (opt->type != OPTT_NULL)
			break ;
		c++;
	}
	return (argv);
}

static char	**prs_fullname(t_trace *tr, char **argv)
{
	char		*name;
	char		*equal;
	t_lstopt	*opt;

	name = (*argv) + 2;
	if (!(*name))
		return (argv);
	equal = ft_strchr(name, '=');
	if (equal)
		*equal = 0;
	opt = opt_byfullname(tr, name);
	if (!(opt))
		prs_fatal(tr, ERR_LUNRECG_OPT, name, true);
	if (equal && opt->type == OPTT_NULL)
		prs_fatal(tr, ERR_ALLOWNOARGS, opt->fullname, true);
	else if (!equal && opt->type == OPTT_NULL)
		opt->handler(tr, opt, NULL);
	else if (equal)
		opt->handler(tr, opt, ++equal);
	else if (!(*(++argv)))
		prs_fatal(tr, ERR_PREQLVAL, name, true);
	else
		opt->handler(tr, opt, *(argv));
	return (argv);
}

void	set_packetsize(t_trace *tr, char *val)
{
	size_t value;

	if (ft_notnumeric(val))
		prs_fatal(tr, ERR_PACKLENV, val, true);
	value = ft_atoul(val);
	if (value > MAX_PACKET)
		prs_fatal(tr, ERR_PACKLENS, val, true);
	else if (value < 28)
		value = 28;
	tr->opts.packetsize = value;
}

/*
** after parsing, sets hosts to argv[] starting at position 1.
*/
void	parse(t_trace *tr, char **argv)
{
	tr->program = *argv;
	argv++;
	while (argv && *argv)
	{
		if (!(ft_strncmp(*argv, "--", 2)))
			argv = prs_fullname(tr, argv);
		else if (!(ft_strncmp(*argv, "-", 1)) && ft_strlen(*argv) > 1)
			argv = prs_shortname(tr, argv);
		else if (!(tr->hostname))
			tr->hostname = *argv;
		else if (!(tr->opts.packetsize))
			set_packetsize(tr, *argv);
		else
			prs_fatal(tr, ERR_EXTRAARG, *argv, true);	
		if (*argv)
			argv++;
	}
	if (!(tr->hostname))
		prs_fatal(tr, ERR_MISSING_HOST, tr->program, true);

}
