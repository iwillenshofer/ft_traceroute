/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 06:56:17 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/23 19:39:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int						my_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static unsigned long long		get_number(const char *str, size_t start)
{
	size_t					i;
	unsigned long			multiplier;
	unsigned long long int	number;

	number = 0;
	multiplier = 1;
	i = start;
	while (ft_isdigit(str[i]) == 1)
		i++;
	if (i == start)
		return (0);
	i--;
	while (i >= start)
	{
		number = number + ((str[i] - '0') * multiplier);
		if (number > LONG_MAX)
			return ((unsigned long long int)(LONG_MAX) + 1);
		multiplier = multiplier * 10;
		if (i == 0)
			break ;
		i--;
	}
	return (number);
}

int								ft_atoi(const char *str)
{
	size_t						i;
	unsigned long long int		number;
	int							signal;

	i = 0;
	signal = 1;
	while (my_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	number = get_number(str, i);
	if (signal == 1 && number > LONG_MAX)
		return (-1);
	if (signal == -1 && number > LONG_MAX)
		return (0);
	number = number * signal;
	return ((int)number);
}
