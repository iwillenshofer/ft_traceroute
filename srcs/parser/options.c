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

#include "ft_ping.h"

static t_lstopt	new_option(char shortcut, char type, char *name)
{
	t_lstopt	new;

	ft_bzero(&new, sizeof(new));
	new.shortcut = shortcut;
	new.type = type;
	ft_strcpy(new.fullname, name);
	return (new);
}

static void	add_descriptions(t_ping *ft_ping)
{
	t_lstopt	*opt;

	opt = ft_ping->opts.available;
	ft_strcpy(opt[OPT_COUNT].desc, ODSC_COUNT);
	ft_strcpy(opt[OPT_INTERVAL].desc, ODSC_INTERVAL);
	ft_strcpy(opt[OPT_NUMERIC].desc, ODSC_NUMERIC);
	ft_strcpy(opt[OPT_TTL].desc, ODSC_TTL);
	ft_strcpy(opt[OPT_VERBOSE].desc, ODSC_VERBOSE);
	ft_strcpy(opt[OPT_TIMEOUT].desc, ODSC_TIMEOUT);
	ft_strcpy(opt[OPT_FLOOD].desc, ODSC_FLOOD);
	ft_strcpy(opt[OPT_PRELOAD].desc, ODSC_PRELOAD);
	ft_strcpy(opt[OPT_PATTERN].desc, ODSC_PATTERN);
	ft_strcpy(opt[OPT_QUIET].desc, ODSC_QUIET);
	ft_strcpy(opt[OPT_SIZE].desc, ODSC_SIZE);
	ft_strcpy(opt[OPT_HELP].desc, ODSC_HELP);
	ft_strcpy(opt[OPT_USAGE].desc, ODSC_USAGE);
	ft_strcpy(opt[OPT_VERSION].desc, ODSC_VERSION);
}

void	add_options(t_ping *ft_ping)
{
	t_lstopt	*opt;

	opt = ft_ping->opts.available;
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
** retrieves an option by fullname.
*/
t_lstopt	*opt_byfullname(t_ping *ft_ping, char *s)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = ft_ping->opts.available;
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
t_lstopt	*opt_byshortcut(t_ping *ft_ping, char c)
{
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	opt = ft_ping->opts.available;
	while (i < OPT_LSTSIZE)
	{
		if (opt[i].shortcut == c)
			return (&(opt[i]));
		i++;
	}
	return (NULL);
}
