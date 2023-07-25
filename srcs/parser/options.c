/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:27:23 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 16:38:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	hndlr_doubleopt(t_ping *ft_ping, t_lstopt *opt, char *value)
{
	(void)ft_ping;(void)opt;(void)(value);
	dprintf(STDOUT_FILENO, "OPTION: %c (%s) --> %s\n", opt->shortcut, opt->fullname, value);
}

void	hndlr_singleopt(t_ping *ft_ping, t_lstopt *opt, char *value)
{
	(void)ft_ping;(void)opt;(void)(value);
	if (opt->shortcut == '?')
		print_help(ft_ping);
	if (opt->shortcut == 'U')
		print_usage(ft_ping);
	if (opt->shortcut == 'n')
		dprintf(STDOUT_FILENO, "OPTION: %c (%s) \n", opt->shortcut, opt->fullname);
	if (opt->shortcut == 'v')
		dprintf(STDOUT_FILENO, "OPTION: %c (%s) \n", opt->shortcut, opt->fullname);
	if (opt->shortcut == 'f')
		dprintf(STDOUT_FILENO, "OPTION: %c (%s) \n", opt->shortcut, opt->fullname);
	if (opt->shortcut == 'q')
		dprintf(STDOUT_FILENO, "OPTION: %c (%s)\n", opt->shortcut, opt->fullname);
	if (opt->shortcut == 'V')
		dprintf(STDOUT_FILENO, "OPTION: %c (%s) \n", opt->shortcut, opt->fullname);
}

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
	opt[OPT_TIMEOUT] .handler = hndlr_doubleopt;
	opt[OPT_SIZE].handler = hndlr_doubleopt;
	opt[OPT_COUNT].handler = hndlr_doubleopt;
	opt[OPT_INTERVAL].handler = hndlr_doubleopt;
	opt[OPT_PRELOAD].handler = hndlr_doubleopt;
	opt[OPT_PATTERN].handler = hndlr_doubleopt;
}

static void	add_descriptions(t_ping *ft_ping)
{
	t_lstopt	*opt;

	opt = ft_ping->options.available;
	ft_strcpy(opt[OPT_COUNT].desc, "stop after sending NUMBER packets");
	ft_strcpy(opt[OPT_INTERVAL].desc,
		"wait NUMBER seconds between sending each packet");
	ft_strcpy(opt[OPT_NUMERIC].desc, "do not resolve host addresses");
	ft_strcpy(opt[OPT_TTL].desc, "specify N as time-to-live");
	ft_strcpy(opt[OPT_VERBOSE].desc, "verbose output");
	ft_strcpy(opt[OPT_TIMEOUT].desc, "stop after N seconds");
	ft_strcpy(opt[OPT_FLOOD].desc, "flood ping");
	ft_strcpy(opt[OPT_PRELOAD].desc,
		"send NUMBER packets as fast as possible \
		before falling into normal mode of behavior");
	ft_strcpy(opt[OPT_PATTERN].desc, "fill ICMP packet with given pattern ");
	ft_strcpy(opt[OPT_QUIET].desc, "quiet output");
	ft_strcpy(opt[OPT_SIZE].desc, "send NUMBER data octets");
	ft_strcpy(opt[OPT_HELP].desc, "give this help list");
	ft_strcpy(opt[OPT_USAGE].desc, "give a short usage message");
	ft_strcpy(opt[OPT_VERSION].desc, "print program version");
}

static t_lstopt	new_option(char shortcut, char type, char *name)
{
	t_lstopt	new;

	ft_bzero(&new, sizeof(new));
	new.shortcut = shortcut;
	new.type = type;
	ft_strcpy(new.fullname, name);
	return (new);
}

void	add_options(t_ping *ft_ping)
{
	t_lstopt	*opt;

	opt = ft_ping->options.available;
	opt[OPT_NUMERIC] = new_option('n', OPTT_NULL, "numeric");
	opt[OPT_VERBOSE] = new_option('v', OPTT_NULL, "verbose");
	opt[OPT_FLOOD] = new_option('f', OPTT_NULL, "flood");
	opt[OPT_QUIET] = new_option('q', OPTT_NULL, "quiet");
	opt[OPT_HELP] = new_option('?', OPTT_NULL, "help");
	opt[OPT_USAGE] = new_option('U', OPTT_NULL, "usage");
	opt[OPT_VERSION] = new_option('V', OPTT_NULL, "version");
	opt[OPT_TTL] = new_option('T', OPTT_SHORT, "ttl");
	opt[OPT_TIMEOUT] = new_option('w', OPTT_SHORT, "timeout");
	opt[OPT_PRELOAD] = new_option('l', OPTT_LONG, "preload");
	opt[OPT_COUNT] = new_option('c', OPTT_LONG, "count");
	opt[OPT_INTERVAL] = new_option('i', OPTT_LONG, "interval");
	opt[OPT_SIZE] = new_option('s', OPTT_LONG, "size");
	opt[OPT_PATTERN] = new_option('p', OPTT_PATTERN, "pattern");
	add_descriptions(ft_ping);
	add_handlers(ft_ping);
}

/*
** retrieves the full name of an option, based on it's shortname.
** ie: returns 'count' for 'c' or 'help' for '?';
*/
const char	*opt_getfullname(t_ping *ft_ping, char c)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = ft_ping->options.available;
	while (i < OPT_OPTIONS_SIZE)
	{
		if (opt[i].shortcut == c)
			return (opt[i].fullname);
		i++;
	}
	return (NULL);
}

/*
** retrieves an option by fullname.
*/
t_lstopt	*opt_byfullname(t_ping *ft_ping, char *s)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = ft_ping->options.available;
	while (i < OPT_OPTIONS_SIZE)
	{
		if (!(ft_strcmp(opt[i].fullname, s)))
			return (&(opt[i]));
		i++;
	}
	return (NULL);
}

/*
** retrieves an option by lastname.
*/
t_lstopt	*opt_byshortcut(t_ping *ft_ping, char c)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = ft_ping->options.available;
	while (i < OPT_OPTIONS_SIZE)
	{
		if (opt[i].shortcut == c)
			return (&(opt[i]));
		i++;
	}
	return (NULL);
}
