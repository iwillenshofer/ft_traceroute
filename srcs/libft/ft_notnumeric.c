/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notnumeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:26:13 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:27:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** returns NULL if all chars are numeric
** otherwise returns the first non numeric pos
*/
char	*ft_notnumeric(char *s)
{
	while (s && *s && ft_isdigit(*s))
		s++;
	if (*s)
		return (s);
	return (NULL);
}
