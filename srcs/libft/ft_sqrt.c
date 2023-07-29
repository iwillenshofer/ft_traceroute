/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 07:56:53 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:26:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Babylonian method for sqrt approximation.
** both res and div converge to the square root as 'res' is the average of res
**  (originally the number of which we want the sqrt) and div (starting at 1).
** Div is then set to original number divided by this average, until res and div
**  are approximated (up to precision), with both converging to the sqrt.
*/

double	ft_sqrt(double number)
{
	long double	res;
	long double	div;
	long double	precision;
	int			min;

	div = 1;
	min = 5;
	res = number;
	precision = 0.0001;
	if (number < 0)
		return (0.0 / 0.0);
	while (min-- > 0 || res - div > precision)
	{
		res = (res + div) / 2;
		div = number / res;
	}
	return (res);
}
