/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:56:58 by iwillens          #+#    #+#             */
/*   Updated: 2023/07/03 14:03:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


char *inetname(struct in_addr *in)
{
	static char line[50];
	struct hostent *hostentity;

	hostentity = gethostbyaddr((char *)in, sizeof (*in), AF_INET);
	if (hostentity && hostentity->h_name) {
		(void) strcpy(line,  hostentity->h_name); 
	}
	return (line);
}

#if BONUS

char *qualified_address(t_ping *ft_ping, struct in_addr *in)
{
	char *ret;

	ret = inetname(in);
	if (!(*ret))
		ret = ft_ping->raw_host;
	ft_bzero(ft_ping->qualified_address, sizeof(ft_ping->qualified_address));
	sprintf(ft_ping->qualified_address, "(%s) %s", ret, inet_ntoa(*in));
	return (ft_ping->qualified_address);
}

#endif
