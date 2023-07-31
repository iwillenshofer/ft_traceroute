/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/31 16:51:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	prs_fatal(t_ping *ft_ping, const char *error,
	const char *s, t_bool shortusage)
{
	dprintf(STDERR_FILENO, error, ft_ping->program, s);
	if (shortusage)
		print_shortusage(ft_ping);
	exit (1);
}

static char	**prs_shortname(t_ping *ft_ping, char **argv)
{
	char		*c;
	t_lstopt	*opt;
	char		err[2];

	err[1] = 0;
	c = (*argv) + 1;
	while (*c)
	{
		err[0] = *c;
		opt = opt_byshortcut(ft_ping, *c);
		if (!opt)
			prs_fatal(ft_ping, ERR_INVALIDOPT, err, true);
		if (opt->type == OPTT_NULL)
			opt->handler(ft_ping, opt, NULL);
		else if (*(++c))
			opt->handler(ft_ping, opt, c);
		else if (!(*(++argv)))
			prs_fatal(ft_ping, ERR_PREQVAL, err, true);
		else
			opt->handler(ft_ping, opt, *(argv));
		if (opt->type != OPTT_NULL)
			break ;
		c++;
	}
	return (argv);
}

static char	**prs_fullname(t_ping *ft_ping, char **argv)
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
	opt = opt_byfullname(ft_ping, name);
	if (!(opt))
		prs_fatal(ft_ping, ERR_LUNRECG_OPT, name, true);
	if (equal && opt->type == OPTT_NULL)
		prs_fatal(ft_ping, ERR_ALLOWNOARGS, opt->fullname, true);
	else if (!equal && opt->type == OPTT_NULL)
		opt->handler(ft_ping, opt, NULL);
	else if (equal)
		opt->handler(ft_ping, opt, ++equal);
	else if (!(*(++argv)))
		prs_fatal(ft_ping, ERR_PREQLVAL, name, true);
	else
		opt->handler(ft_ping, opt, *(argv));
	return (argv);
}

/*
** after parsing, sets hosts to argv[] starting at position 1.
*/
void	parse(t_ping *ft_ping, char **argv)
{
	char	**orig_args;
	size_t	hosts_pos;

	orig_args = argv;
	hosts_pos = 0;
	ft_ping->program = *argv;
	argv++;
	while (argv && *argv)
	{
		if (!(ft_strncmp(*argv, "--", 2)))
			argv = prs_fullname(ft_ping, argv);
		else if (!(ft_strncmp(*argv, "-", 1)) && ft_strlen(*argv) > 1)
			argv = prs_shortname(ft_ping, argv);
		else
			orig_args[++hosts_pos] = *argv;
		if (*argv)
			argv++;
	}
	if (!hosts_pos)
		prs_fatal(ft_ping, ERR_MISSING_HOST, ft_ping->program, true);
	orig_args[++hosts_pos] = NULL;
}
