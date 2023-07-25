/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/25 16:52:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	prs_fatal_chr(t_ping *ft_ping, const char *error,
	const char c, t_bool shortusage)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = 0;
	prs_fatal(ft_ping, error, buf, shortusage);
}

/*
** if option was shortened, value will only be accepted if it is next to '='
**  otherwise, accept it on the next argv.
** ie: -c5 and -c 5 are both valids, but --count=5 is valid and --count= 5
**  is not.
*/
char	**prs_options(t_ping *ft_ping, char **argv)
{
	char	*s;
	char	*begin;
	t_bool	shortened;

	s = ++(*argv);
	begin = s;
	while (*s)
	{
		shortened = false;
		if ((*s == '-') && s == begin)
			shortened = prs_shorten_options(ft_ping, s);
		if (ft_strrchr(OPTS_SINGLE, *s))
			prs_single(ft_ping, *s);
		else if (ft_strrchr(OPTS_DOUBLE, *s))
			return (prs_double(ft_ping, s, argv, shortened));
		else
		{
			if (!(ft_strlen(s) == 1 && *s == '-'))
				prs_fatal(ft_ping, ERR_INVALIDOPT, s, true);
		}
		s++;
	}
	return (argv);
}

void	prs_fatal(t_ping *ft_ping, const char *error,
	const char *s, t_bool shortusage)
{
	dprintf(STDERR_FILENO, error, ft_ping->program, s);
	if (shortusage)
		print_shortusage(ft_ping);
	exit (1);
}

char	**prs_shortname(t_ping *ft_ping, char **argv)
{
	char		*c;
	t_lstopt 	*opt;
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
		else
		{
			if (*(++c))
				opt->handler(ft_ping, opt, c);
			else
			{
				if (!(*(++argv)))
					prs_fatal(ft_ping, ERR_PREQVAL, err, true);
				opt->handler(ft_ping, opt, *(argv));
			}
			break;
		}
		c++;
	}
	return (argv);
}

char	**prs_fullname(t_ping *ft_ping, char **argv)
{
	char		*name;
	char		*equal;
	t_lstopt 	*opt;

	name = (*argv) + 2;
	if (!(*name))
		return (argv);
	equal = ft_strchr(name, '=');
	if (equal)
		*equal = 0;
	opt = opt_byfullname(ft_ping, name);
	if (!(opt))
		prs_fatal(ft_ping, ERR_LUNRECG_OPT, name, true);
	if (equal)
	{
		*equal = '=';
		opt->handler(ft_ping, opt, ++equal);
	}
	else
	{
		if (!(*(++argv)))
			prs_fatal(ft_ping, ERR_PREQLVAL, name, true);
		opt->handler(ft_ping, opt, *(argv));
	}
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
	hosts_pos = 1;
	ft_ping->program = *argv;
	argv++;
	while (argv && *argv)
	{
		if (!(ft_strncmp(*argv, "--", 2))) /* must be fullname */
			argv = prs_fullname(ft_ping, argv);
		else if (!(ft_strncmp(*argv, "-", 1)) && ft_strlen(*argv) > 1)  /* must be shortcut */
			argv = prs_shortname(ft_ping, argv);
		else
		{
			orig_args[hosts_pos] = *argv;
			hosts_pos++;
		}
		if (*argv)
			argv++;
	}
	if (hosts_pos == 1)
		prs_fatal(ft_ping, ERR_MISSING_HOST, ft_ping->program, true);
	orig_args[hosts_pos] = NULL;
}
