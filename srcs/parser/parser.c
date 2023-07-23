/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/23 12:30:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
**
*/
char	**parse_options(t_ping *ft_ping, char **argv)
{
	char *s;

	s = ++(*argv);
	while (*s)
	{
		if (*s == 'h')
		{
			print_usage(ft_ping);
			exit(0);
		}
		else if (*s == 'v')
		{
			printf("SETTING VERBOSE\n");
		}
		else
		{
			printf("invalid option -- '%c'\n", *s);
			print_usage(ft_ping);
			exit(0);
		}
		s++;
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
	if (ft_arglen(argv) == 1)
		fatal(ft_ping, NULL, true);
	argv++;
	while (argv && *argv)
	{
		if (**argv == '-')
			argv = parse_options(ft_ping, argv);
		else
		{
			orig_args[hosts_pos] = *argv;
			hosts_pos++;
		}
		if (*argv)
			argv++;
	}
	if (hosts_pos == 1)
		fatal(ft_ping, get_errorstr(ft_ping, ERROR_INVALID_ARGUMENTS, ft_ping->program, NULL), true);
	orig_args[hosts_pos] = NULL;
}
