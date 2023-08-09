/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:16:08 by iwillens          #+#    #+#             */
/*   Updated: 2023/08/09 00:16:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*v1;
	unsigned char	*v2;

	i = 0;
	v1 = (unsigned char *)(s1);
	v2 = (unsigned char *)(s2);
	while (i < n)
	{
		if (v1[i] != v2[i])
			return (v2[i] - v1[i]);
		i++;
	}
	return (0);
}
