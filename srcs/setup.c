/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:42:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/19 13:28:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this file sets up the ft_ping structure.
*/

#include "ft_ping.h"

/*
**
*/
char	**parse_options(t_ping *ft_ping, char **argv)
{
	char *s;
	
	(void)ft_ping;
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
	char **orig_args;


	size_t hosts;
	orig_args = argv;
	hosts = 1;
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
			orig_args[hosts] = *argv;
			hosts++;
		}
		if (argv)
			argv++;
	}
	if (hosts == 1)
		fatal(ft_ping, get_errorstr(ft_ping, ERROR_INVALID_ARGUMENTS, ft_ping->program, NULL), true);
	orig_args[hosts] = NULL;
}

void	set_default_pattern(t_ping *ft_ping)
{
	return ;
	size_t	i;

	i = 0;
	while (i < DFL_CUSTOM_PATTERN_SIZE)
	{
		ft_ping->options.echo.pattern.pattern[i] = i;
		i++;
	}
	ft_ping->options.echo.pattern.size = DFL_CUSTOM_PATTERN_SIZE;
}

void	set_defaults(t_ping *ft_ping)
{
	ft_ping->options.echo.size = DFL_PACKET_SIZE;
	ft_ping->options.all.ttl = DFL_TTL;
	set_default_pattern(ft_ping);
}

void	setup(t_ping *ft_ping, char **argv)
{
	ft_bzero(ft_ping, sizeof(t_ping));
	set_defaults(ft_ping);
	parse(ft_ping, argv);
	/*
	** initial options that should be parsed.
	*/
	ft_ping->options.all.ttl = 0;
	ft_ping->options.all.count = 3;



	ft_ping->pid = getpid();
}