/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:13:56 by iwillens          #+#    #+#             */
/*   Updated: 2023/06/30 17:01:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t array_len(char **s)
{
	size_t i;

	i = 0;
	while (s && (s[i]))
		i++;
	return (i);
}

char **push_back(char **arr, char *str)
{
	size_t len;
	char **s;
	size_t i;

	if (!str || !(ft_strlen(str)))
		return (arr);
	len = array_len(arr);
	s = malloc(sizeof(char*) * (len + 2));
	if (!(s))
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = arr[i];
		i++;
	}
	s[i] = ft_strdup(str);
	s[i + 1] = NULL;
	free(arr);
	return (s);
}

char	*findspace(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (!(s[i]))
		return (&(s[i]));
	s[i] = 0;
	i++;
	return (&(s[i]));
}

char 	**ft_split(char *src)
{
	char **ret;
	char *s;
	char *next;
	char *begin;

	ret = NULL;
	s = ft_strdup(src);
	begin = s;
	while (begin && *begin)
	{
		next = findspace(begin);
		ret = push_back(ret, begin);
		begin = next;
	}
	free(s);
	return (ret);
}
