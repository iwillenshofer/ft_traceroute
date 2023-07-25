/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:08:03 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 08:52:56 by iwillens         ###   ########.fr       */
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
