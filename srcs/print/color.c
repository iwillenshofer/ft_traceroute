/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:42:56 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/10 15:41:23 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** prints a new color only if it is different of the previous color
** (or there is no previous color.).
** Then, it current color exists, sets it to the new values.
*/
void	color(t_trace *tr, char new_color, char new_opt)
{
	if (!tr->opts.color)
		return ;
	if (new_color == RESET)
	{
		ft_putstr("\033[0m");
		return ;
	}
	ft_putstr("\033[0;");
	if (new_color)
	{
		ft_putnbr(new_opt);
		ft_putchar(';');
	}
	ft_putnbr(new_color);
	ft_putchar('m');
}
