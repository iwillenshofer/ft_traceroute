/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:02:43 by iwillens          #+#    #+#             */
/*   Updated: 2020/01/22 08:18:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int i;

	i = ft_strlen(s);
	if (s[i] == '\0' && (char)c == '\0')
		return ((char*)&s[i]);
	while (i--)
		if (s[i] == (char)c)
			return ((char*)&s[i]);
	return (NULL);
}
