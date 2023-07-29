/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nothex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:23:47 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:27:24 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** returns NULL if all chars are hex, otherwise returns the first not hex pos
*/
char	*ft_nothex(char *s)
{
	while (s && *s && ft_ishex(*s))
		s++;
	if (*s)
		return (s);
	return (NULL);
}
