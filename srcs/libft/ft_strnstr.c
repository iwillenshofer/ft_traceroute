/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:16:50 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/30 01:25:43 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_str(const char *haystack, const char *needle,
		size_t needle_len, size_t pos)
{
	size_t	j;
	int		found;

	j = 0;
	found = 1;
	while (j < needle_len)
	{
		if (haystack[pos + j] != needle[j])
		{
			found = 0;
			break ;
		}
		j++;
	}
	if (found == 1)
		return ((char *)&haystack[pos]);
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle,
		size_t len)
{
	size_t		i;
	long long	max_len;
	size_t		needle_len;
	char		*found;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	max_len = ft_strlen(haystack) - needle_len;
	if (max_len < 0)
		return (NULL);
	i = 0;
	while (i <= (size_t)max_len && i < len && i <= len - needle_len)
	{
		found = find_str(haystack, needle, needle_len, i);
		if (found)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
