/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/08/10 20:34:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

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
			prs_fatal_pos(tr, ERR_INVALIDOPT, argv);
		if (opt->type == OPTT_NULL)
			opt->handler(tr, opt, NULL);
		else if (*(++c))
			opt->handler(tr, opt, c);
		else if (!(*(++argv)))
			prs_fatal(tr, ERR_PREQVAL, err, false);
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
		prs_fatal_pos(tr, ERR_INVALIDOPT, argv);
	if (equal && opt->type == OPTT_NULL)
		prs_fatal(tr, ERR_ALLOWNOARGS, opt->fullname, false);
	else if (!equal && opt->type == OPTT_NULL)
		opt->handler(tr, opt, NULL);
	else if (equal)
		opt->handler(tr, opt, ++equal);
	else if (!(*(++argv)))
		prs_fatal(tr, ERR_PREQLVAL, name, false);
	else
		opt->handler(tr, opt, *(argv));
	return (argv);
}

static void	set_packetsize(t_trace *tr, char *val, char **pos)
{
	size_t	value;

	if (ft_notnumeric(val))
		prs_fatal_pos(tr, ERR_PACKLENV, pos);
	value = ft_atoul(val);
	if (value > MAX_PACKET)
		prs_fatal(tr, ERR_PACKLENS, val, false);
	else if (value < 28)
		value = 28;
	tr->opts.packetsize = value;
}

/*
** after parsing, sets hosts to argv[] starting at position 1.
*/
void	parse(t_trace *tr, char **argv)
{
	tr->argv.program = *argv;
	argv++;
	while (argv && *argv)
	{
		if (!(ft_strncmp(*argv, "--", 2)))
			argv = prs_fullname(tr, argv);
		else if (!(ft_strncmp(*argv, "-", 1)) && ft_strlen(*argv) > 1)
			argv = prs_shortname(tr, argv);
		else if (!(tr->argv.hostname))
		{
			tr->argv.hostpos = argv;
			tr->argv.hostname = *argv;
		}
		else if (!(tr->opts.packetsize))
			set_packetsize(tr, *argv, argv);
		else
			prs_fatal_pos(tr, ERR_EXTRAARG, argv);
		if (*argv)
			argv++;
	}
	if (!(tr->argv.hostname))
		print_help(tr);
}
