/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:13:29 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/29 22:38:34 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
** special handler for pattern.
**  -p, --pattern=PATTERN 
** parses an hex pattern into ft_ping->options.pattern.pattern
*/
void	hndlr_pattern(t_ping *ft_ping, t_lstopt *opt, char *value)
{
	size_t	size;
	char	c;

	size = 0;
	c = 0;
	while (value && *value && size < MAX_PATTERN && opt)
	{
		if (ft_isdigit(*value))
			*value = *value - '0';
		else if ((ft_ishex(*value)))
			*value = (*value - 'a') + 10;
		else
			prs_fatal(ft_ping, ERR_PPATTERN, value, false);
		if ((size % 2))
			c = c << 4;
		c += *value;
		ft_ping->options.pattern.pattern[size / 2] = c;
		if ((size % 2))
			c = 0;
		size++;
		value++;
	}
	ft_ping->options.pattern.size = size / 2;
	if (size % 2 || !size)
		ft_ping->options.pattern.size = (size / 2) + 1;
}

/*
** -i, --interval=NUMBER 
** accepts decimal values.
*/
void	hndlr_interval(t_ping *ft_ping,
		t_lstopt *opt __attribute__((unused)), char *value)
{
	char	*dec;
	size_t	mask;
	char	errbuf[ERR_BUF + 1];

	if ((++(ft_ping->options.int_set) && ft_ping->options.flood))
		prs_fatal(ft_ping, ERR_INCOMP_INTFLOOD, NULL, false);
	dec = ft_strchr(value, '.');
	snprintf(errbuf, ERR_BUF, "`%s' near `%s'", value, ft_notnumeric(value));
	if (ft_strlen(value) && ft_notnumeric(value)
		&& (ft_notnumeric(value) != dec || ft_strlen(value) == 1))
		prs_fatal(ft_ping, ERR_PVALUE, errbuf, true);
	if (dec && *(++dec))
		snprintf(errbuf, ERR_BUF, "`%s' near `%s'", value, ft_notnumeric(dec));
	if (dec && ft_notnumeric(dec))
		prs_fatal(ft_ping, ERR_PVALUE, errbuf, true);
	if (dec)
		*(dec - 1) = 0;
	ft_ping->options.interval.tv_sec = ft_atoul(value);
	mask = 100000;
	while (dec && *dec && mask)
	{
		ft_ping->options.interval.tv_usec += ((*dec - '0') * mask);
		mask = mask / 10;
		dec++;
	}
}

/*
** here are handled all options that need an argument
** except -p, pattern. and -i, --interval
**  -c, --count=NUMBER    
**  -T, --ttl=N           
**  -w, --timeout=N       
**  -l, --preload=NUMBER  
**  -s, --size=NUMBER     
*/
void	hndlr_doubleopt(t_ping *ft_ping, t_lstopt *opt, char *value)
{
	size_t	val;
	char	errbuf[ERR_BUF + 1];

	snprintf(errbuf, ERR_BUF, "`%s' near `%s'", value, ft_notnumeric(value));
	if ((ft_notnumeric(value)))
		prs_fatal(ft_ping, ERR_PVALUE, errbuf, false);
	val = ft_atoul(value);
	if ((opt->shortcut == 'T' && val > 255)
		|| (opt->shortcut == 'w' && val > INT_MAX)
		|| (opt->shortcut == 's' && val > MAX_PACKET_SIZE))
		prs_fatal(ft_ping, ERR_PTOOBIG, value, false);
	else if (opt->shortcut == 'l' && val > INT_MAX)
		prs_fatal(ft_ping, ERR_PPRELOAD, value, false);
	else if (val == 0 && (opt->shortcut == 'T' || opt->shortcut == 'w'))
		prs_fatal(ft_ping, ERR_VALTOOSMALL, value, false);
	if (opt->shortcut == 'c')
		ft_ping->options.count = val;
	else if (opt->shortcut == 'T')
		ft_ping->options.ttl = val;
	else if (opt->shortcut == 'w')
		ft_ping->options.timeout.tv_sec = val;
	else if (opt->shortcut == 'l')
		ft_ping->options.preload = val;
	else if (opt->shortcut == 's')
		ft_ping->options.size = val;
}

/*
** here are handled all options that do not need an argument
**  -n, --numeric         
**  -v, --verbose         
**  -f, --flood           
**  -q, --quiet           
**  -?, --help            
**  -U, --usage           
**  -V, --version         
*/
void	hndlr_singleopt(t_ping *ft_ping, t_lstopt *opt, char *value)
{
	(void)(value);
	if (opt->shortcut == '?')
		print_help(ft_ping);
	if (opt->shortcut == 'U')
		print_usage(ft_ping);
	if (opt->shortcut == 'V')
		print_version(ft_ping);
	if (opt->shortcut == 'n')
		ft_ping->options.numeric = true;
	if (opt->shortcut == 'v')
		ft_ping->options.verbose = true;
	if (opt->shortcut == 'f')
		ft_ping->options.flood = true;
	if (opt->shortcut == 'q')
		ft_ping->options.quiet = true;
	if (ft_ping->options.flood && ft_ping->options.int_set)
		prs_fatal(ft_ping, "%s: -f and -i incompatible options\n", NULL, false);
}

/*
** add the option handlers, so the parser can call
** the apropriate function.
*/
void	add_handlers(t_ping *ft_ping)
{
	t_lstopt	*opt;

	opt = ft_ping->options.available;
	opt[OPT_QUIET].handler = hndlr_singleopt;
	opt[OPT_HELP].handler = hndlr_singleopt;
	opt[OPT_USAGE].handler = hndlr_singleopt;
	opt[OPT_VERSION].handler = hndlr_singleopt;
	opt[OPT_NUMERIC].handler = hndlr_singleopt;
	opt[OPT_VERBOSE].handler = hndlr_singleopt;
	opt[OPT_FLOOD].handler = hndlr_singleopt;
	opt[OPT_TTL].handler = hndlr_doubleopt;
	opt[OPT_TIMEOUT].handler = hndlr_doubleopt;
	opt[OPT_SIZE].handler = hndlr_doubleopt;
	opt[OPT_COUNT].handler = hndlr_doubleopt;
	opt[OPT_INTERVAL].handler = hndlr_interval;
	opt[OPT_PRELOAD].handler = hndlr_doubleopt;
	opt[OPT_PATTERN].handler = hndlr_pattern;
}
