/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:42:43 by iwillens          #+#    #+#             */
/*   Updated: 2023/06/30 16:46:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
/*
** this version of ft_strjoin frees s1.
*/
char *ft_strjoin(char *s1, char *s2)
{
	char *s;
	int i;

	i = 0;
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		s[i] = *s2;
		i++;
		s2++;
	}
	s[i] = 0;
	free(s1);
	return (s);
}
