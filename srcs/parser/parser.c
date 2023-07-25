/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/25 11:47:21 by iwillens         ###   ########.fr       */
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
	if (ft_arglen(argv) == 1)
		prs_fatal(ft_ping, ERR_MISSING_HOST, ft_ping->program, true);
	argv++;
	while (argv && *argv)
	{
		if (**argv == '-' && ft_strlen(*argv) != 1)
			argv = prs_options(ft_ping, argv);
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
