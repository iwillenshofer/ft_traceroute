/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shorten.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:11:49 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/25 11:23:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	shorten(char *s, char *option, char shortcut)
{
	size_t	str_size;
	size_t	new_size;

	str_size = ft_strlen(s);
	*s = shortcut;
	ft_strcpy(s + 1, s + 1 + ft_strlen(option));
	new_size = ft_strlen(s);
	ft_bzero(s + new_size, str_size - new_size);
}

static t_bool	try_shorten(char *s, char *option, char shortcut)
{
	size_t	option_len;

	option_len = ft_strlen(option);
	if (!(ft_strncmp(s + 1, option, option_len)))
	{
		if (s[option_len + 1] != '=' && s[option_len + 1] != '\0')
			return (false);
		shorten(s, option, shortcut);
		return (true);
	}
	return (false);
}

/*
** shortens the option in a string, making --count = -c
*/
t_bool	prs_shorten_options(t_ping *ft_ping, char *s)
{
	t_bool		find;
	t_lstopt	*opt;
	size_t		i;

	i = 0;
	find = false;
	opt = ft_ping->options.available;
	while (i < OPT_OPTIONS_SIZE)
	{
		find |= try_shorten(s, opt[i].fullname, opt[i].shortcut);
		i++;
	}
	if (!find)
	{
		if (ft_strlen(s) == 1)
			return (false);
		prs_fatal(ft_ping, ERR_UNRECOGNIZED_OPTION, --s, true);
	}
	return (find);
}
