/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:08:03 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/28 14:41:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_help(t_ping *ft_ping)
{
	t_lstopt *opt;
	size_t i;
	char	buf[64];
	char	*type;
	i=0;
	opt = ft_ping->options.available;

	dprintf(STDOUT_FILENO, "Usage: %s [OPTION...] HOST ...\n", ft_ping->program);
	dprintf(STDOUT_FILENO, "Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	dprintf(STDOUT_FILENO, "Options valid for all request types:\n\n");
	while (i < OPT_OPTIONS_SIZE)
	{
		bzero(buf, sizeof(buf));
		ft_strcpy(buf, opt[i].fullname);
		if (opt[i].type == OPTT_LONG)
			type = "=NUMBER";
		else if (opt[i].type == OPTT_SHORT)
			type = "=N";
		else if (opt[i].type == OPTT_PATTERN)
			type = "=PATTERN";
		if (opt[i].type != OPTT_NULL)
			ft_strcpy(buf + ft_strlen(buf), type);
		dprintf(STDOUT_FILENO, "  -%c, --%-21s %s\n", opt[i].shortcut, buf, opt[i].desc);
		i++;
	}
	dprintf(STDOUT_FILENO, "\nMandatory or optional arguments to long options are also mandatory or optional \
for any corresponding short options.\n");
	exit(0);
}

static size_t print_option(t_ping *ft_ping, char c, t_bool full)
{
	size_t	i;
	t_lstopt *opt;
	char *type;

	type = "";
	i = 0;
	opt = ft_ping->options.available;
	while (i < OPT_OPTIONS_SIZE)
	{
		if (opt[i].shortcut == c)
		{
			if (!full && opt[i].type == OPTT_NULL)
				return (0);
			if (opt[i].type == OPTT_LONG)
				type = "NUMBER";
			else if (opt[i].type == OPTT_SHORT)
				type = "N";
			else if (opt[i].type == OPTT_PATTERN)
				type = "PATTERN";
			if (full && opt[i].type == OPTT_NULL)
				return (dprintf(STDERR_FILENO, " [--%s]", opt[i].fullname));
			else if (full)
				return (dprintf(STDERR_FILENO, " [--%s=%s]", opt[i].fullname, type));
			return (dprintf(STDERR_FILENO, " [-%c %s]", c, type));
		}
		i++;
	}
	return (0);
}

static int		prt_options(t_ping *ft_ping, char *options, t_bool full, int used, int preceeding)
{
	char *opts;

	opts = options;
	while (*opts)
	{
		if (used >= 70)
		{
			dprintf(STDERR_FILENO, "\n%*s", preceeding, "");
			used = preceeding;
		}
		used += print_option(ft_ping, *opts, full);
		opts++;
	}
	return (used);
}

void	print_usage(t_ping *ft_ping)
{
	int			preceeding;
	int			used;

	preceeding = dprintf(STDERR_FILENO, "Usage: %s", ft_ping->program);
	used = preceeding + dprintf(STDERR_FILENO, " [-%s]", OPTS_SINGLE);
	used = prt_options(ft_ping, OPTS_DOUBLE, false, used, preceeding);
	used = prt_options(ft_ping, OPTS_SINGLE, true, used, preceeding);
	used = prt_options(ft_ping, OPTS_DOUBLE, true, used, preceeding);
	dprintf(STDERR_FILENO, " HOST ...\n");
	exit(0);
}

void	print_shortusage(t_ping *ft_ping)
{
	dprintf(STDERR_FILENO, ERR_SRTUSAGE, ft_ping->program, ft_ping->program);
}

void	print_version(t_ping *ft_ping)
{
	dprintf(STDOUT_FILENO, "\033[37;1m%s Version 0.%u\033[0m\n", ft_ping->program, UINT_MAX);
	dprintf(STDOUT_FILENO, "\033[0m\033[38;2;123;145;255m _         _  _  _\n");
	dprintf(STDOUT_FILENO, "\033[38;2;87;115;255m<_> _ _ _ <_>| || | ___ ._ _  ___\n");
	dprintf(STDOUT_FILENO, "\033[38;2;207;59;255m| || | | || || || |/ ._>| ' |<_-<\n");
	dprintf(STDOUT_FILENO, "\033[38;2;255;135;255m|_||__/_/ |_||_||_|\\___.|_|_|/__/\033[0m\n\n");
	dprintf(STDOUT_FILENO, "\033[37;1m      * * *   ft_ping   * * *\033[0m\n\n");
	exit(0);
}
