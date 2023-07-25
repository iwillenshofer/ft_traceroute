/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:19:27 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 11:29:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	check_numeric(t_ping *ft_ping, char *s, char c)
{
	char	*orig;
	char	errbuf[128];

	ft_bzero(errbuf, sizeof(errbuf));
	orig = s;
	if (c != 'p' && (*s == '-' || *s == '+'))
		s++;
	while (*s)
	{
		if (c != 'p' && !(ft_isdigit(*s)))
		{
			sprintf(errbuf, "`%s' near `%s'", orig, s);
			prs_fatal(ft_ping, ERR_PVALUE, errbuf, false);
		}
		else if (c == 'p' && s - orig < MAX_PATTERN && *s && !(ft_ishex(*s)))
			prs_fatal(ft_ping, ERR_PPATTERN, s, false);
		s++;
	}
}

void	prs_values(t_ping *ft_ping, char c, char *value)
{
	unsigned long	val;

	val = 0;
	if (c == 'p')
		prs_value_pattern(ft_ping, value);
	else
	{
		if (value && *value)
			val = ft_atoul(value);
		if (c == 'T')
			prs_value_ttl(ft_ping, val, value);
		else if (c == 'w')
			prs_value_timeout(ft_ping, val, value);
		else if (c == 'c')
			prs_value_count(ft_ping, val);
		else if (c == 'i')
			prs_value_interval(ft_ping, val);
		else if (c == 's')
			prs_value_size(ft_ping, val, value);
		else if (c == 'l')
			prs_value_preload(ft_ping, val, value);
	}
}

/*
** possible double parsing:
** interval count preload size (32bits), ttl timeout (8bits), pattern=hex
*/
char	**prs_double(t_ping *ft_ping, char *p, char **argv, t_bool shortened)
{
	char	c;
	char	errbuf[128];

	ft_bzero(errbuf, sizeof(errbuf));
	c = *p;
	p++;
	if (!shortened && *p == '=')
	{
		sprintf(errbuf, "`%s' near `%s'", p, p);
		prs_fatal(ft_ping, ERR_PVALUE, errbuf, false);
	}
	if (shortened && *p == '=')
		p++;
	if (!(*p))
		p = *(++argv);
	if (!p && shortened)
		prs_fatal(ft_ping, ERR_PREQLVAL, opt_getfullname(ft_ping, c), true);
	else if (!p && !(shortened))
	{
		sprintf(errbuf, "%c", c);
		prs_fatal(ft_ping, ERR_PREQVAL, errbuf, true);
	}
	check_numeric(ft_ping, p, c);
	prs_values(ft_ping, c, p);
	return (argv);
}
