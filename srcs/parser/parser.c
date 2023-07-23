/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:22:38 by marvin            #+#    #+#             */
/*   Updated: 2023/07/23 23:24:23 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	validate_digits(char c, char *s, char **argv, t_bool shortened)
{
	(void)s;(void)c;(void)argv;(void)shortened;
}

void	shorten(char *s, char *option, char shortcut)
{
	size_t	str_size;
	size_t	new_size;

	str_size = ft_strlen(s);
	*s = shortcut;
	ft_strcpy(s + 1, s + ft_strlen(option));
	new_size = ft_strlen(s);
	ft_bzero(s + new_size, str_size - new_size);
}

t_bool	try_shorten(char *s, char *option, char shortcut)
{
	if (!(ft_strncmp(s, option, ft_strlen(option))))
	{
		shorten(s, option, shortcut);
		return (true);
	}
	return (false);
}

t_bool	shorten_options(char *s)
{
	t_bool find;

	find = false;
	find |= try_shorten(s, "-count", 'c');
	find |= try_shorten(s, "-interval", 'i');
	find |= try_shorten(s, "-numeric", 'n');
	find |= try_shorten(s, "-ttl", 'T');
	find |= try_shorten(s, "-verbose", 'v');
	find |= try_shorten(s, "-timeout", 'w');
	find |= try_shorten(s, "-flood", 'f');
	find |= try_shorten(s, "-preload", 'l');
	find |= try_shorten(s, "-pattern", 'p');
	find |= try_shorten(s, "-quiet", 'q');
	find |= try_shorten(s, "-size", 's');
	find |= try_shorten(s, "-help", '?');
	find |= try_shorten(s, "-usage", 'U');
	find |= try_shorten(s, "-version", 'V');
	if (!find)
		printf("Thats an invalid option!!!\n");
	return (find);
}

void	parse_single(t_ping *ft_ping, char c)
{
	(void)ft_ping;(void)c;
}

#define DECIMAL 1
#define HEXADECIMAL 2

void	parse_fatal(t_ping *ft_ping, char *error, char *s1, char *s2)
{
	printf(error, ft_ping->program, s1, s2);
	exit (1);
}

void	check_numeric(t_ping *ft_ping, char *s, char c)
{
	char	*orig;
	int		type;

	orig = s;
	type = DECIMAL;
	if (c == 'p')
		type = HEXADECIMAL;
	if (type == DECIMAL && (*s == '-' || *s == '+'))
		s++;
	while (*s)
	{
		if (type == DECIMAL && !(ft_isdigit(*s)))
			parse_fatal(ft_ping, ERR_PARSE_VALUE, orig, s);
		else if (type == HEXADECIMAL && s - orig < MAX_PATTERN && *s && !(ft_ishex(*s)))
			parse_fatal(ft_ping, ERR_PARSE_PATTERN, s, NULL);
		s++;
	}
}

void	parse_values(t_ping *ft_ping, char c, char *value)
{
	unsigned long val;

	val = 0;
	if (c == 'p')
		parse_value_pattern(ft_ping, value);
	else
	{
		if (value && *value)
			val = ft_atoul(value);
		if (c == 'T')
			parse_value_ttl(ft_ping, val, value);
		else if (c == 'w')
			parse_value_timeout(ft_ping, val, value);
		else if (c == 'c')
			parse_value_count(ft_ping, val);
		else if (c == 'i')
			parse_value_interval(ft_ping, val);
		else if (c == 's')
			parse_value_size(ft_ping, val, value);
		else if (c == 'l')
			parse_value_preload(ft_ping, val, value);
	}
}
/*
** possible double parsing:
** interval count preload size (32bits), ttl timeout (8bits), pattern=hex
*/
char	**parse_double(t_ping *ft_ping, char *p, char **argv, t_bool shortened)
{
	char c;

	c = *p;
	p++;
	if (shortened && *p != '=')
		parse_fatal(ft_ping, ERR_UNRECOGNIZED_OPTION, *argv, NULL);
	if (shortened)
		p++;
	if (!(*p) && !shortened)
		p = *(++argv);
	check_numeric(ft_ping, p, c);
	parse_values(ft_ping, c, p);
	return (argv);
}

/*
** if option was shortened, value will only be accepted if it is next to '='
**  otherwise, accept it on the next argv.
** ie: -c5 and -c 5 are both valids, but --count=5 is valid and --count= 5
**  is not.
*/
char	**parse_options(t_ping *ft_ping, char **argv)
{
	char *s;
	char *begin;
	t_bool shortened;

	s = ++(*argv);
	begin = s;
	while (*s)
	{
		shortened = false;
		if ((*s == '-') && s == begin)
			shortened = shorten_options(s);
		if (ft_strrchr(OPTS_SINGLE, *s))
			parse_single(ft_ping, *s);
		else if (ft_strrchr(OPTS_DOUBLE, *s))
			return(parse_double(ft_ping, s, argv, shortened));
		else
		{
			/*huston, we have a problem! */
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
